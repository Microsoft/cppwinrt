
WINRT_EXPORT namespace winrt
{
    [[nodiscard]] inline auto resume_foreground(
        Windows::System::DispatcherQueue const& dispatcher,
        Windows::System::DispatcherQueuePriority const priority = Windows::System::DispatcherQueuePriority::Normal) noexcept
    {
        struct awaitable
        {
            awaitable(Windows::System::DispatcherQueue const& dispatcher, Windows::System::DispatcherQueuePriority const priority) noexcept :
                m_dispatcher(dispatcher),
                m_priority(priority)
            {
            }

            bool await_ready() const noexcept
            {
                return false;
            }

            bool await_resume() const noexcept
            {
                return m_queued;
            }

            bool await_suspend(std::experimental::coroutine_handle<> handle)
            {
                bool const queued = m_dispatcher.TryEnqueue(m_priority, [handle, this]
                {
                    m_ready.wait();
                    handle();
                });
                m_queued = queued;
                m_ready.signal(); // all member variables potentially invalid after this point

                return queued;
            }

        private:
            Windows::System::DispatcherQueue const& m_dispatcher;
            Windows::System::DispatcherQueuePriority const m_priority;
            bool m_queued{};
            slim_event m_ready;
        };

        return awaitable{ dispatcher, priority };
    };

#ifdef __cpp_coroutines
    inline auto operator co_await(Windows::System::DispatcherQueue const& dispatcher)
    {
        return resume_foreground(dispatcher);
    }
#endif
}