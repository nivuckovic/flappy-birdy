#pragma once

namespace ID {
	enum class Textures {
		BACKGROUND,
		OBSTACLE,
		FLAPPY,

		LENGTH
	};

	enum class Fonts {
		ARIAL,

		LENGTH
	};
}

namespace StateStack {
	enum class Action {
		PUSH,
		POP,

		LENGTH
	};
}