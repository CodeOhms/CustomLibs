Import('env')

opt = env.Clone(CCFLAGS = '-O2')
dbg = env.Clone(CCFLAGS = '-O0 -g')

Export('env', 'opt', 'dbg')

SConscript(['File_System_Tools/SConscript',
            'Log_Tools/SConscript',
            'Misc_Tools/Thermal_Tools/SConscript',
            'Misc_Tools/Time_Tools/SConscript'])
