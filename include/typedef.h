
 /*
    This file is part of Binsh.

    Binsh is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Binsh is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Binsh.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file typedef.h
 * @author Antoine Sauray
 * @date 14 April 2016
 * @brief useful types
 */


#ifndef TYPEDEF_H
#define TYPEDEF_H

/**
 * The pointer to command type
 */
typedef int (*cmdPtr)(int, char*[]);

#endif