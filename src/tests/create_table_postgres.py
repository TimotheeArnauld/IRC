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

    cursor.execute("DROP TABLE IF EXISTS Salon")
    cursor.execute("CREATE TABLE Salon(Id SERIAL PRIMARY KEY,Name VARCHAR(255) NOT NULL,Id_User VARCHAR(255),Name_User VARCHAR(255))")
    cursor.execute("INSERT INTO Salon(Name,Id_User,Name_User) VALUES('General',101,'Julien')")
    cursor.execute("INSERT INTO Salon(Name,Id_User,Name_User) VALUES('Test',102,'Timothee')")
    cursor.execute("INSERT INTO Salon(Name,Id_User,Name_User) VALUES('Projet',103,'Yousria')")
    cursor.execute("INSERT INTO Salon(Name,Id_User,Name_User) VALUES('Projet annuel',104,'Paul')")

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
