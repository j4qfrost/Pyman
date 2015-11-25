import compileall
import importlib
import sys

def recompile():
    compileall.compile_dir('.', force=True)

def reload(module_name):
	module_name = module_name.replace("/",".")
	try:
		if module_name in sys.modules:
			del sys.modules[module_name]
			importlib.import_module(module_name)
			print("Successfully reloaded: " + module_name)
		else:
			print(sys.modules)
			print("Failed to reload: " + module_name)
	except:
		print("Housten we have a problem...")


