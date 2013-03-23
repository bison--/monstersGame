env = DefaultEnvironment()
env['CXX'] = '/usr/bin/g++-4.5'
env['CXXFLAGS'] = '-std=c++0x -Wall -Wextra -fno-strict-aliasing -fstack-protector -D_FORTIFY_SOURCE=2'

Program('monstersGame', [Glob('*.cpp')], LIBS=[])
