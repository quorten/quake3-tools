#ifndef MD3_FIX
#define MD3_FIX
/*
--------------------------------------------------------------------------------

MD3Fix

(c) 2003 Randy Reddig

To compile on Unix: gcc -o md3fix md3fix.c

Quake III Arena MD3 model fixer. Fixes bad shader names, corrupted
vertex normals, and misc other stuff.

Note: this code contains no byte-swapping code, and therefore can only
be run on a little endian architecture.

Portions of this code were borrowed from my PicoModel library, which is
used in GtkRadiant and Q3Map2, licensed under the BSD license.

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation.

This file is provided AS IS with no warranties of any kind.  The author
shall have no liability with respect to the infringement of copyrights,
trade secrets or any patents by this file or any part thereof.  In no
event will the author be liable for any lost revenue or profits or
other special, indirect and consequential damages.

--------------------------------------------------------------------------------

PicoModel Library 

Copyright (c) 2002, Randy Reddig & seaw0lf
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list
of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

Neither the names of the copyright holders nor the names of its contributors may
be used to endorse or promote products derived from this software without
specific prior written permission. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

--------------------------------------------------------------------------------
*/



/*
dependencies
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>



/*
macros
*/

#define MD3FIX_VERSION		"0.2"
#define DIR_SEP				'/'



/*
types
*/

/* md3 model format */
#define MD3_MAGIC			"IDP3"
#define MD3_VERSION			15

/* md3 vertex scale */
#define MD3_SCALE		  (1.0f / 64.0f)

/* md3 model frame information */
typedef struct md3Frame_s
{
	float		bounds[ 2 ][ 3 ];
	float		localOrigin[ 3 ];
	float		radius;
	char		creator[ 16 ];
}
md3Frame_t;

/* md3 model tag information */
typedef struct md3Tag_s
{
	char		name[ 64 ];
	float		origin[ 3 ];
	float		axis[ 3 ][ 3 ];
}
md3Tag_t;

/* md3 surface md3 (one object mesh) */
typedef struct md3Surface_s
{
	char		magic[ 4 ];
	char		name[ 64 ];		/* polyset name */
	int			flags;
	int			numFrames;		/* all model surfaces should have the same */
	int			numShaders;		/* all model surfaces should have the same */
	int			numVerts;
	int			numTriangles;
	int			ofsTriangles;
	int			ofsShaders;		/* offset from start of md3Surface_t */
	int			ofsSt;			/* texture coords are common for all frames */
	int			ofsVertexes;	/* numVerts * numFrames */
	int			ofsEnd;			/* next surface follows */
}
md3Surface_t;

typedef struct md3Shader_s
{
	char		name[ 64 ];
	int			shaderIndex;	/* for ingame use */
}
md3Shader_t;

typedef struct md3Triangle_s
{
	int			indexes[ 3 ];
}
md3Triangle_t;

typedef struct md3TexCoord_s
{
	float		st[ 2 ];
}
md3TexCoord_t;

typedef struct md3Vertex_s
{
	short		xyz[ 3 ];
	short		normal;
}
md3Vertex_t;


/* md3 model file md3 structure */
typedef struct md3_s
{
	char		magic[ 4 ];		/* MD3_MAGIC */
	int			version;
	char		name[ 64 ];		/* model name */
	int			flags;
	int			numFrames;
	int			numTags;
	int			numSurfaces;
	int			numSkins;		/* number of skins for the mesh */
	int			ofsFrames;		/* offset for first frame */
	int			ofsTags;		/* numFrames * numTags */
	int			ofsSurfaces;	/* first surface, others follow */
	int			ofsEnd;			/* end of file */
}
md3_t;

//Prototypes
//int MD3FixMain( char* src, char* dest );

#endif