#ifndef __SCENES_H__
#define __SCENES_H__

#include "../types/types.h"
#include <stdlib.h>
#include <string.h>

#define SCENE_FUNCTIONS_DECLARATION(name) \
	void name##Destroy(name* scene); \
	void name##Init(name* scene); \
	void name##Update(name* scene); \
    void name##Input(name* scene)

#define CREATE_SCENE_DEFINITION(name) \
	name* name##Create(Game* parent) { \
		name* scene = (name*) malloc(sizeof(name)); \
		memset(scene, 0, sizeof(name)); \
		scene->parent = parent; \
		name##Init(scene); \
		return scene; \
	}

SceneMenu* SceneMenuCreate(Game* parent);
SCENE_FUNCTIONS_DECLARATION(SceneMenu);

ScenePlay* ScenePlayCreate(Game* parent, Vec2 drawableZone);
SCENE_FUNCTIONS_DECLARATION(ScenePlay);
void ScenePlayNewGame(ScenePlay* scene);

#endif
/*
 *	End Of File
 */