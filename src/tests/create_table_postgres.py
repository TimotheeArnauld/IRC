#!/usr/bin/python

import psycopg2
import sys

def create_tables():
    conn = None
    try:

        conn_string = "host='localhost' dbname='docker' user='docker' password='docker'"
        print "Connecting to database\n	->%s" % (conn_string)
        con = psycopg2.connect(conn_string)
        cursor = con.cursor()
        print "Connected!\n"

        cursor.execute("DROP TABLE IF EXISTS users CASCADE")
    	cursor.execute("DROP TABLE IF EXISTS rooms CASCADE")
    	cursor.execute("DROP TABLE IF EXISTS users_rooms CASCADE")
    	cursor.execute("CREATE TABLE users (user_id SERIAL PRIMARY KEY,user_name VARCHAR(255) NOT NULL,user_password VARCHAR(255) NOT NULL)")
    	cursor.execute("CREATE TABLE rooms (room_id SERIAL PRIMARY KEY,room_name VARCHAR(255) NOT NULL)")
    	cursor.execute("CREATE TABLE users_rooms (user_id INTEGER NOT NULL,room_id INTEGER NOT NULL,PRIMARY KEY (room_id , user_id),FOREIGN KEY (user_id) REFERENCES users (user_id) ON UPDATE CASCADE ON DELETE CASCADE,FOREIGN KEY (room_id) REFERENCES rooms (room_id) ON UPDATE CASCADE ON DELETE CASCADE)")

        cursor.execute("INSERT INTO users VALUES(101,'Julien','toto')")
        cursor.close()
        con.commit()
        print "Table ok\n"

    except psycopg2.DatabaseError, e:

        if con:
            con.rollback()

        print 'Error %s' % e
        sys.exit(1)


    finally:

        if con:
            con.close()

if __name__ == '__main__':
    create_tables()
