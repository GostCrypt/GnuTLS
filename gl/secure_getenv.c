/* Look up an environment variable more securely.

   Copyright 2013-2016 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <config.h>

#include <stdlib.h>

#if !HAVE___SECURE_GETENV
# if HAVE_ISSETUGID
#  include <unistd.h>
# else
#  undef issetugid
#  ifdef _WIN32
#   define issetugid() 0
#  else
#   define issetugid() 1
#  endif
# endif
#endif

char *
secure_getenv (char const *name)
{
#if HAVE___SECURE_GETENV
  return __secure_getenv (name);
#else
  if (issetugid ())
    return 0;
  return getenv (name);
#endif
}