FROM fedora:43

WORKDIR /workspace

RUN dnf update -y && dnf install -y \
			ccache \
			clang \
			clang-tools-extra \
			cmake \
			curl \
			doxygen \
			gcc \
			gcc-c++ \
			git \
			graphviz \
			make \
			ninja-build \
			python3 \
			python3-pip \
			tar \
			unzip \
			vim \
		&& dnf clean all

RUN pip install --no-cache-dir conan

RUN git clone https://github.com/google/googletest.git /opt/googletest && \
    mkdir /opt/googletest/build && \
    cd /opt/googletest/build && \
    cmake .. \
        -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/usr/local && \
    ninja && \
    ninja install && \
    rm -rf /opt/googletest
