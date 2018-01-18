#!/usr/bin/python
# -*- coding: utf-8 -*-

import psycopg2
import sys


con = None

try:

    conn_string = "host='localhost' dbname='docker' user='docker' password='docker'"
    print "Connecting to database\n	->%s" % (conn_string)
    con = psycopg2.connect(conn_string)
    cursor = con.cursor()
    print "Connected!\n"

    cursor.execute("SELECT * FROM Salon")

    rows = cursor.fetchall()

    for row in rows:
        print row


except psycopg2.DatabaseError, e:
    print 'Error %s' % e
    sys.exit(1)


finally:

    if con:
        con.close()
