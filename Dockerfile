# Basic image
FROM ubuntu:22.04

# Set DEBIAN_FRONTEND to noninteractive
ENV DEBIAN_FRONTEND=noninteractive

# Install basic and GStreamer dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    wget \
    unzip \
    libgstreamer1.0-dev \
    libgstreamer-plugins-base1.0-dev \
    libgstreamer-plugins-bad1.0-dev \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-plugins-ugly \
    gstreamer1.0-libav gstreamer1.0-tools \
    gstreamer1.0-x \
    gstreamer1.0-alsa \
    gstreamer1.0-gl \
    gstreamer1.0-gtk3 \
    gstreamer1.0-qt5 \
    gstreamer1.0-pulseaudio \
    && rm -rf /var/lib/apt/lists/*

# Download and install OpenCV
RUN wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip && \
    mkdir opencv && unzip opencv.zip -d opencv && \
    mkdir -p /opencv/build && cd /opencv/build && \
    cmake -DCMAKE_BUILD_TYPE=Release ../opencv-4.x && \
    cmake --build . -j$(nproc) && ldconfig && \
    cd / && rm -rf opencv.zip

# Set the working directory
WORKDIR /usr/src/app

# Copy the source code
COPY . .

# Compile
RUN mkdir -p build && cd build && \
    cmake .. && \
    cmake --build . -j$(nproc)

RUN ls -la

# Expose the port
EXPOSE 5004

# Set command to run the application
CMD ["./build/app/MotionDetection"]
