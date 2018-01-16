# Set the base image to Ubuntu
FROM ubuntu

# File Author / Maintainer
MAINTAINER Timothee Arnauld

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
RUN apt-get install -y python2.7 python-dev
RUN apt-get install -y wget
RUN apt-get install -y man
RUN apt-get install -y net-tools
RUN apt-get install -y libncurses-dev
RUN apt-get install -y cmake
RUN wget https://bootstrap.pypa.io/get-pip.py

# Install pip
RUN python2.7 get-pip.py

# Install python dependancies
RUN pip install psycopg2
RUN pip install cryptography

# Install IRC sources
RUN git clone https://github.com/TimotheeArnauld/IRC.git ~/IRC
RUN echo "export PYTHONPATH=$PYTHONPATH:/root/IRC/src/client/modules" >> ~/.bashrc
RUN cd ~/IRC

RUN git clone --depth=1 https://github.com/amix/vimrc.git ~/.vim_runtime
RUN sh ~/.vim_runtime/install_awesome_vimrc.sh

RUN service postgresql start