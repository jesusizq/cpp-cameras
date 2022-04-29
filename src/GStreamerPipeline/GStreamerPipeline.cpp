#include <GStreamerPipeline.hpp>
#include <iostream>

GStreamerPipeline::GStreamerPipeline(std::string_view pipelineDescription)
    : pipelineDescription(pipelineDescription) {
  gst_init(nullptr, nullptr);
}

bool GStreamerPipeline::initialize() {
  pipeline = std::unique_ptr<GstElement, GstElementDeleter>(
      gst_parse_launch(pipelineDescription.c_str(), nullptr));
  if (pipeline.get() == nullptr) {
    return false;
  }
  return true;
}
