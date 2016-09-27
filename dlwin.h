/*  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef DLWIN_H_66813C40_78B8_11E6_B633_005056C00008_INCLUDED_
#define DLWIN_H_66813C40_78B8_11E6_B633_005056C00008_INCLUDED_

#define RTLD_LAZY   0x00000001
#define RTLD_NOEW   0x00000002
void* dlopen(const char* filename, int flags);
int dlclose(void* handle);
void* dlsym(void* handle, const char* name);
char* dlerror(void);

#endif

