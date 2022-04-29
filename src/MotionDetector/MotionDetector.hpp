#ifndef MOTIONDETECTOR_HPP
#define MOTIONDETECTOR_HPP

#include <vector>

enum class Motion { MOTION, NO_MOTION };

template <typename A> class MockMotionDetector final {
public:
  Motion detect(const A &previous_frame, const A &current_frame) {
    return index > mock_motion.size() ? Motion::NO_MOTION
                                      : mock_motion[++index];
  }

private:
  const std::vector<Motion> mock_motion = {
      Motion::NO_MOTION, Motion::NO_MOTION, Motion::NO_MOTION,
      Motion::MOTION,    Motion::MOTION,    Motion::MOTION,
      Motion::MOTION,    Motion::MOTION,    Motion::MOTION,
      Motion::MOTION,    Motion::MOTION,    Motion::MOTION,
      Motion::MOTION,    Motion::MOTION,    Motion::MOTION,
      Motion::MOTION,    Motion::MOTION,    Motion::MOTION,
      Motion::MOTION,    Motion::MOTION,    Motion::MOTION,
      Motion::MOTION,    Motion::MOTION,    Motion::MOTION,
      Motion::MOTION,    Motion::MOTION,    Motion::MOTION,
      Motion::MOTION,    Motion::MOTION,    Motion::MOTION,
      Motion::NO_MOTION, Motion::NO_MOTION, Motion::NO_MOTION};

  std::uint64_t index = 0;
};

#endif // MOTIONDETECTOR_HPP
