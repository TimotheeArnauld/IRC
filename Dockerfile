# Set the base image to Ubuntu
FROM ubuntu

# File Author / Maintainer
MAINTAINER Timothee Arnauld

# Go to root directory
RUN cd

# Update the repository sources list
RUN apt-get update

# Install Git, PostgreSQL, Python 2.7, GCC
RUN apt-get install -y git
RUN apt-get install -y postgresql
RUN apt-get install -y make build-essential
RUN apt-get update
RUN apt-get install -y sqlite3 libsqlite3-dev
RUN apt-get install -y libssl-dev
RUN apt-get install -y vim
RUN echo "alias python='python3.5'" >> .bashrc
RUN /bin/bash -c "source ~/.bashrc"
RUN apt-get install -y wget
RUN wget https://bootstrap.pypa.io/get-pip.py

# Install pip
RUN python3.5 get-pip.py

# Install python dependancies
RUN pip install psycopg2
RUN pip install cryptography

# Install IRC sources
RUN git clone https://github.com/TimotheeArnauld/IRC.git
RUN cd IRC
