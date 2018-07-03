#pragma once

enum Type {
	TRANSFORM,
	MESH
};

class Component {
public:
	Component() {}
	Type type;
};
