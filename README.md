# README #

### How to install? ###

* git clone https://github.com/TimotheeArnauld/IRC.git ~/IRC
* cd ~/IRC

For docker users:
* *$> docker build -t IRC .*
* *$>docker images*
* *$> docker run -ti IMAGEID*
* *$> cd ~/IRC/src/server*
* *$> ./server*
* *$> start*

In another terminal instance:
* *$> docker ps*
* *$> docker exec -ti CONTAINERID bash*
* *$> cd ~/IRC/src/client*
* *$> ./client*
  
### To compile sources ###

In each directory (server/client), you just need to execute the following command line:

* *$> make*

### Python dependencies ###

Use *pip install* to install the followings modules:

* cryptography
* psycopg2

### About the authors ###

This program is written and maintained by:

* *Timothée **ARNAULD** *
* *Yousria **BENCHADI** *
* *Julien **BERTAUD** *
