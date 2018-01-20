#include "command.h"

char* command_analyse(char s[256]){
	PyObject *pName, *pModule, *pFunction, *pArg, *pValue;
	pName = PyString_FromString("builder");
	pModule = PyImport_Import(pName);
	pArg = PyTuple_New(1);
	PyTuple_SetItem(pArg, 0, PyString_FromString(s));
	pFunction = PyObject_GetAttrString(pModule, "queryBuilder");
	char *command =  PyString_AsString(PyObject_CallObject(pFunction, pArg));

	if(strcmp(command, "-1") == 0){
		return "-1";
	}else{
		if(strcmp(command, "0") == 0){
			exit(0);
		}
		else{
			return command;
		}
	}

	return "-1";
} 