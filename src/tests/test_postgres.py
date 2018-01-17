#!/usr/bin/python
import psycopg2
import sys
 
def main():
	conn_string = "host='localhost' dbname='docker' user='docker' password='docker'"
	print "Connecting to database\n	->%s" % (conn_string)
	conn = psycopg2.connect(conn_string)
	cursor = conn.cursor()
	print "Connected!\n"
 
if __name__ == "__main__":
	main()

