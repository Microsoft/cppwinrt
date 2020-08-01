#include "pch.h"

#include <numeric>
#include <shared_mutex>

#include "multi_threaded_common.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

// Map correctness tests exist elsewhere. These tests are strictly geared toward testing multi threaded functionality
//
// Be careful with use of REQUIRE.
//
// 1. REQUIRE is not concurrency-safe. Don't call it from two threads simultaneously.
// 2. The number of calls to REQUIRE should be the consistent in the face of nondeterminism.
//    This makes the "(x assertions in y test cases)" consistent.
//
// If you need to check something from a background thread, or where the number
// of iterations can vary from run to run, use winrt::check_bool, which still
// fails the test but doesn't run afoul of REQUIRE's limitations.

template <typename T>
static void test_single_reader_single_writer(IMap<int, T> const& map)
{
    static constexpr int final_size = 10000;

    // Insert / HasKey / Lookup
    unique_thread t([&]
    {
        for (int i = 0; i < final_size; ++i)
        {
            map.Insert(i, conditional_box<T>(i));
            std::this_thread::yield();
        }
    });

    while (true)
    {
        int i = 0;
        auto beginSize = map.Size();
        for (; i < final_size; ++i)
        {
            if (!map.HasKey(i))
            {
                check_bool(static_cast<uint32_t>(i) >= beginSize);
                break;
            }

            check_bool(conditional_unbox(map.Lookup(i)) == i);
        }

        if (i == final_size)
        {
            break;
        }
    }
}

template <typename T>
static void test_iterator_invalidation(IMap<int, T> const& map)
{
    static constexpr int size = 10;

    // Remove / Insert / First / HasCurrent / MoveNext / Current
    for (int i = 0; i < size; ++i)
    {
        map.Insert(i, conditional_box<T>(i));
    }

    volatile bool done = false;
    unique_thread t([&]
    {
        // Since the underlying storage is std::map, it's actually quite hard to hit UB that has an observable side
        // effect, making it hard to have a meaningful test. The idea here is to remove and re-insert the "first"
        // element in a tight loop so that enumeration is likely to hit a concurrent access that's actually meaningful.
        // Even then, failures really only occur with a single threaded collection when building Debug
        while (!done)
        {
            map.Remove(0);
            map.Insert(0, conditional_box<T>(0));
        }
    });

    int exceptionCount = 0;

    for (int i = 0; i < 10000; ++i)
    {
        try
        {
            int count = 0;
            for (auto itr = map.First(); itr.HasCurrent(); itr.MoveNext())
            {
                auto pair = itr.Current();
                check_bool(pair.Key() == conditional_unbox(pair.Value()));
                ++count;
            }
            check_bool(count >= (size - 1));
            check_bool(count <= size);
        }
        catch (hresult_changed_state const&)
        {
            ++exceptionCount;
        }
    }
    done = true;

    // In reality, this number should be quite large; much larger than the 50 validated here
    REQUIRE(exceptionCount >= 50);
}

template <typename T>
static void test_concurrent_iteration(IMap<int, T> const& map)
{
    static constexpr int size = 10000;

    // Current / HasCurrent
    {
        for (int i = 0; i < size; ++i)
        {
            map.Insert(i, conditional_box<T>(i));
        }

        auto itr = map.First();
        unique_thread threads[2];
        int increments[std::size(threads)] = {};
        for (int i = 0; i < std::size(threads); ++i)
        {
            threads[i] = unique_thread([&itr, &increments, i]
            {
                int last = -1;
                while (true)
                {
                    try
                    {
                        // NOTE: Because there is no atomic "get and increment" function on IIterator, the best we can do is
                        // validate that we're getting valid increasing values, e.g. as opposed to validating that we read
                        // all unique values.
                        auto val = itr.Current().Key();
                        check_bool(val > last);
                        check_bool(val < size);
                        last = val;
                        if (!itr.MoveNext())
                        {
                            break;
                        }

                        // MoveNext is the only synchronized operation that has a predictable side effect we can validate
                        ++increments[i];
                    }
                    catch (hresult_error const&)
                    {
                        // There's no "get if" function, so concurrent increment past the end is always possible...
                        check_bool(!itr.HasCurrent());
                        break;
                    }
                }
            });
        }

        for (auto& t : threads)
        {
            t.join();
        }

        REQUIRE(!itr.HasCurrent());

        auto totalIncrements = std::accumulate(std::begin(increments), std::end(increments), 0);
        REQUIRE(totalIncrements == (size - 1));
    }

    // HasCurrent / GetMany
    {
        auto itr = map.First();
        unique_thread threads[2];
        int totals[std::size(threads)] = {};
        for (int i = 0; i < std::size(threads); ++i)
        {
            threads[i] = unique_thread([&itr, &totals, i]
            {
                IKeyValuePair<int, T> vals[10];
                while (itr.HasCurrent())
                {
                    // Unlike 'Current', 'GetMany' _is_ atomic in regards to read+increment
                    auto len = itr.GetMany(vals);
                    totals[i] += std::accumulate(vals, vals + len, 0, [](int curr, auto const& next) { return curr + next.Key(); });
                }
            });
        }

        for (auto& t : threads)
        {
            t.join();
        }

        // sum(i = 1 -> N){i} = N * (N + 1) / 2
        auto total = std::accumulate(std::begin(totals), std::end(totals), 0);
        REQUIRE(total == (size * (size - 1) / 2));
    }
}

template <typename T>
static void test_multi_writer(IMap<int, T> const& map)
{
    // Large enough that several threads should be executing concurrently
    static constexpr uint32_t size = 10000;
    static constexpr size_t threadCount = 8;

    // Insert
    unique_thread threads[threadCount];
    for (int i = 0; i < threadCount; ++i)
    {
        threads[i] = unique_thread([&map, i]
        {
            auto off = i * size;
            for (int j = 0; j < size; ++j)
            {
                map.Insert(j + off, conditional_box<T>(j));
            }
        });
    }

    for (auto& t : threads)
    {
        t.join();
    }

    REQUIRE(map.Size() == (size * threadCount));

    // Since we know that the underlying collection type is std::map, the keys should be ordered
    int expect = 0;
    for (auto&& pair : map)
    {
        REQUIRE(pair.Key() == expect++);
    }
}

template <typename K, typename V>
struct exclusive_map :
    map_base<exclusive_map<K, V>, K, V>,
    implements<exclusive_map<K, V>, IMap<K, V>, IMapView<K, V>, IIterable<IKeyValuePair<K, V>>>
{
    std::map<K, V> container;
    mutable std::shared_mutex mutex;

    auto& get_container() noexcept
    {
        return container;
    }

    auto& get_container() const noexcept
    {
        return container;
    }

    // It is not safe to recursively acquire an SRWLOCK, even in shared mode, however this is unchecked by the SRWLOCK
    // implementation. Using a vector that only performs exclusive operations is the simplest way to validate that
    // the implementation does not attempt to recursively acquire the mutex.
    template <typename Func>
    auto perform_exclusive(Func&& fn) const
    {
        // Exceptions are better than deadlocks...
        REQUIRE(mutex.try_lock());
        std::lock_guard guard(mutex, std::adopt_lock);
        return fn();
    }
};

struct map_deadlock_object : implements<map_deadlock_object, IReference<int>>
{
    int m_value;
    exclusive_map<int, IReference<int>>* m_vector;

    map_deadlock_object(int value, exclusive_map<int, IReference<int>>* vector) :
        m_value(value),
        m_vector(vector)
    {
    }

    ~map_deadlock_object()
    {
        // NOTE: This will crash on failure, but that's better than actually deadlocking
        REQUIRE(m_vector->mutex.try_lock());
        m_vector->mutex.unlock();
    }

    int Value() const noexcept
    {
        return m_value;
    }
};

static void deadlock_test()
{
    auto map = make_self<exclusive_map<int, IReference<int>>>();

    map->Insert(0, make<map_deadlock_object>(0, map.get()));
    map->Insert(1, make<map_deadlock_object>(1, map.get()));
    REQUIRE(map->Size() == 2);
    REQUIRE(map->HasKey(0));
    REQUIRE(!map->HasKey(2));
    REQUIRE(map->Lookup(0).Value() == 0);
    map->Remove(0);
    REQUIRE(map->Size() == 1);
    map->Clear();
    REQUIRE(map->Size() == 0);

    map->Insert(0, make<map_deadlock_object>(0, map.get()));
    map->Insert(1, make<map_deadlock_object>(1, map.get()));
    auto view = map->GetView();
    REQUIRE(view.Size() == 2);
    REQUIRE(view.HasKey(0));
    REQUIRE(view.Lookup(1).Value() == 1);

    auto itr = map->First();
    REQUIRE(itr.HasCurrent());
    REQUIRE(itr.Current().Key() == 0);
    REQUIRE(itr.MoveNext());
    REQUIRE(!itr.MoveNext());
    REQUIRE(!itr.HasCurrent());
}

TEST_CASE("multi_threaded_map")
{
    test_single_reader_single_writer(multi_threaded_map<int, int>());
    test_single_reader_single_writer(multi_threaded_map<int, IInspectable>());

    test_iterator_invalidation(multi_threaded_map<int, int>());
    test_iterator_invalidation(multi_threaded_map<int, IInspectable>());

    test_concurrent_iteration(multi_threaded_map<int, int>());
    test_concurrent_iteration(multi_threaded_map<int, IInspectable>());

    test_multi_writer(multi_threaded_map<int, int>());
    test_multi_writer(multi_threaded_map<int, IInspectable>());

    deadlock_test();
}

TEST_CASE("multi_threaded_observable_map")
{
    test_single_reader_single_writer<int>(multi_threaded_observable_map<int, int>());
    test_single_reader_single_writer<IInspectable>(multi_threaded_observable_map<int, IInspectable>());

    test_iterator_invalidation<int>(multi_threaded_observable_map<int, int>());
    test_iterator_invalidation<IInspectable>(multi_threaded_observable_map<int, IInspectable>());

    test_concurrent_iteration<int>(multi_threaded_observable_map<int, int>());
    test_concurrent_iteration<IInspectable>(multi_threaded_observable_map<int, IInspectable>());

    test_multi_writer<int>(multi_threaded_observable_map<int, int>());
    test_multi_writer<IInspectable>(multi_threaded_observable_map<int, IInspectable>());
}
