#ifndef FRAMEQUEUE_HPP
#define FRAMEQUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

template <typename T> class FrameQueue {
public:
  FrameQueue() = default;
  ~FrameQueue() = default;
  FrameQueue(const FrameQueue &) = delete;
  FrameQueue &operator=(const FrameQueue &) = delete;
  FrameQueue(FrameQueue &&) = delete;
  FrameQueue &operator=(FrameQueue &&) = delete;

  void push(const T &frame) {
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(frame);
  }

  bool tryPop(T &frame) {
    std::lock_guard<std::mutex> lock(mutex);
    if (queue.empty()) {
      return false;
    }
    frame = std::move(queue.front());
    queue.pop();
    return true;
  }

private:
  std::queue<T> queue;
  std::mutex mutex;
};

#endif // FRAMEQUEUE_HPP
