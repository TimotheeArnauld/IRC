def queryBuilder(message):
	queries = ["/quit", "/help", "/list", "/file","/join", "/leave", "/create", "/signin", "/signup"]
	query = ""

	if message.find("/quit") == 0:
		query = "0"

	if message.find("/help") == 0:
		query = "1"

	if message.find("/list") == 0:
		query = "2"

	if message.find("/file") == 0:
		query = "3"

	if message.find("/join") == 0:
		tmp = message.split(" ")
		tmp.pop(0)
		for i in tmp:
			query += ";" + i
		query = "4" + query
		if query.count(";") != 1:
			query = "-1"

	if message.find("/leave") == 0:
		query = "5"

	if message.find("/create") == 0:
		tmp = message.split(" ")
		tmp.pop(0)
		for i in tmp:
			query += ";" + i
		query = "6" + query
		if query.count(";") != 1:
			query = "-1"


	if message.find("/signin") == 0:
		tmp = message.split(" ")
		tmp.pop(0)
		for i in tmp:
			query += ";" + i
		query = "7" + query
		if query.count(";") != 2:
			query = "-1"

	if message.find("/signup") == 0:
		tmp = message.split(" ")
		tmp.pop(0)
		for i in tmp:
			query += ";" + i
		query = "8" + query
		if query.count(";") != 2:
			query = "-1"

	return query


# if __name__ == '__main__':
#     queryBuilder("/quit")
#     queryBuilder("/help")
#     queryBuilder("/list")
#     queryBuilder("/file")
#     queryBuilder("/join roomesgi")
#     queryBuilder("/leave")
#     queryBuilder("/create roomtmp")
#     queryBuilder("/signin timothee test1234")
#     queryBuilder("/signup usertest test7894")