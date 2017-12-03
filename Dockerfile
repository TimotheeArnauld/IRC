# Set the base image to Ubuntu
FROM ubuntu

# File Author / Maintainer
MAINTAINER Timothee Arnauld

# Update the repository sources list
RUN apt-get update

# Install Git, PostgreSQL, Python 2.7, GCC
RUN apt-get install -y git
RUN apt-get install -y build-essential
RUN apt-get install -y python2.7 
RUN apt-get install -y postgresql

# Install pip
RUN python get-pip.py

# Install python dependancies
RUN pip install psycopg2
RUN pip install cryptography

# Install IRC sources
RUN cd
RUN git clone https://github.com/TimotheeArnauld/IRC.git
RUN cd IRC
