# Set the base image to Ubuntu
FROM ubuntu

# File Author / Maintainer
MAINTAINER Timothee Arnauld

# Update the repository sources list
RUN apt-get update

# Install Git, PostgreSQL, Python 2.7, GCC
RUN apt-get install git
RUN apt-get install build-essential
RUN apt-get install python2.7 
RUN apt-get install postgresql

# Install pip
RUN python get-pip.py

# Install python dependancies
RUN pip install psycopg2
RUN pip install cryptography