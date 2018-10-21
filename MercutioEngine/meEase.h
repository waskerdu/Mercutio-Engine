#pragma once

#ifndef PI
#define PI  3.14159265
#endif
class Back {
	
	public:
		
		static float easeIn(float t,float b , float c, float d);
		static float easeOut(float t,float b , float c, float d);
		static float easeInOut(float t,float b , float c, float d);
		
};

class Bounce {
	
	public:
		
		static float easeIn(float t,float b , float c, float d);
		static float easeOut(float t,float b , float c, float d);
		static float easeInOut(float t,float b , float c, float d);
};

class Circ {
	
	public:
		
		static float easeIn(float t,float b , float c, float d);
		static float easeOut(float t,float b , float c, float d);
		static float easeInOut(float t,float b , float c, float d);
};

class Cubic {
	
	public:
		
		static float easeIn(float t,float b , float c, float d);
		static float easeOut(float t,float b , float c, float d);
		static float easeInOut(float t,float b , float c, float d);
};

class Elastic {
	
	public:
		
		static float easeIn(float t ,float b = 0.0f , float c = 1.0f, float d = 1.0f);
		static float easeOut(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
		static float easeInOut(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
};

class Expo {
	
	public:
		
		static float easeIn(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
		static float easeOut(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
		static float easeInOut(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
};

class Linear {
	
	public:

		static float easeNone(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
		static float easeIn(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
		static float easeOut(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
		static float easeInOut(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
};

class Quad {
	
	public:
		
		static float easeIn(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
		static float easeOut(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
		static float easeInOut(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
};

class Quart {
	
	public:
		
		static float easeIn(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
		static float easeOut(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
		static float easeInOut(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
};

class Quint {
	
	public:
		
		static float easeIn(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
		static float easeOut(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
		static float easeInOut(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
};

class Sine {
	
	public:
		
		static float easeIn(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
		static float easeOut(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
		static float easeInOut(float t, float b = 0.0f, float c = 1.0f, float d = 1.0f);
};