FROM debian:wheezy
RUN apt-get update && apt-get install -y \
     build-essential \
     git \
     liblapack-dev \
     libopenblas-dev \
     openmpi-bin \
     libopenmpi-dev \
	 nano \
 && apt-get clean
