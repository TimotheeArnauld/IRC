#!/usr/bin/python
import psycopg2


def create_tables():
    """ create tables in the PostgreSQL database"""
    commands = (
        """
        CREATE TABLE users (
        	user_id SERIAL PRIMARY KEY,
            user_name VARCHAR(255) NOT NULL,
            user_password VARCHAR(255) NOT NULL
        )
        """,
        """ CREATE TABLE rooms (
                room_id SERIAL PRIMARY KEY,
                room_name VARCHAR(255) NOT NULL
                )
        """,
        """
        CREATE TABLE users_rooms (
                user_id INTEGER NOT NULL,
                room_id INTEGER NOT NULL,
                PRIMARY KEY (room_id , user_id),
                FOREIGN KEY (user_id)
                    REFERENCES users (user_id)
                    ON UPDATE CASCADE ON DELETE CASCADE,
                FOREIGN KEY (room_id)
                    REFERENCES rooms (room_id)
                    ON UPDATE CASCADE ON DELETE CASCADE
        )
        """)
    conn = None
    try:
        # connect to the PostgreSQL server
        conn = psycopg2.connect("dbname=docker user=docker host=localhost password=docker")
        cur = conn.cursor()
        # create table one by one
        for command in commands:
            cur.execute(command)
        # close communication with the PostgreSQL database server
        cur.close()
        # commit the changes
        conn.commit()
    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        if conn is not None:
            conn.close()
 
 
if __name__ == '__main__':
    create_tables()