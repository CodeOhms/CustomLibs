env = Environment( CC = 'g++', CCCOMSTR = "Compiling $TARGET",
                   LINKCOMSTR = "Linking $TARGET" )

Export('env')

SConscript('SConscript', variant_dir='build', duplicate=0)
