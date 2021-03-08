
#
# MIT License
#
# Copyright(c) 2018 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

#===============================================================================
# Binaries Sources and Objects
#===============================================================================

# Binary
ARCHIVE = $(LIBGOMP25)

# C Source Files
SRC = workaround.c config/nanvix/mutex.c config/nanvix/sem.c config/nanvix/bar.c\
	  config/nanvix/proc.c alloc.c error.c env.c barrier.c team.c parallel.c\
	
	  
	  
#	  barrier.c
#workaround.c error.c alloc.c libgomp.c config/proc.c config/sem.c config/mutex.c config/lock.c \
	   config/bar.c splay-tree.c task.c priority_queue.c work.c team.c parallel.c\
#	   icv.c# #  env.c 

OBJ = $(SRC:.c=.$(OBJ_SUFFIX).o)

#===============================================================================

include $(BUILDDIR)/makefile.archive
