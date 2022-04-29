#ifndef GSTREAMERPIPELINE_HPP
#define GSTREAMERPIPELINE_HPP

#include <gst/gst.h>
#include <memory>
#include <string>

class GStreamerPipeline {
public:
  GStreamerPipeline() = delete;
  GStreamerPipeline(std::string_view pipelineDescription);
  ~GStreamerPipeline() { stop(); };
  GStreamerPipeline Pipeline(const GStreamerPipeline &) = delete;
  GStreamerPipeline &operator=(const GStreamerPipeline &) = delete;
  GStreamerPipeline(GStreamerPipeline &&) = delete;
  GStreamerPipeline &operator=(GStreamerPipeline &&) = delete;

  bool initialize();
  void start() { gst_element_set_state(pipeline.get(), GST_STATE_PLAYING); }
  void stop() { gst_element_set_state(pipeline.get(), GST_STATE_NULL); }

private:
  struct GstElementDeleter {
    void operator()(GstElement *p) { gst_object_unref(p); }
  };

  std::unique_ptr<GstElement, GstElementDeleter> pipeline{nullptr};
  std::string pipelineDescription;
};

#endif // GSTREAMERPIPELINE_HPP
