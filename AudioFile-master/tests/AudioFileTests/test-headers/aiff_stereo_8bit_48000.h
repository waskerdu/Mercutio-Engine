#include <vector>

namespace aiff_stereo_8bit_48000 { 

int numSamplesPerChannel = 384000;
int bitDepth = 8;
int sampleRate = 48000;
int numChannels = 2;

std::vector<std::vector<double>> testBuffer = {{-0.0078125, 0.0234375, -0.1015625, -0.0703125, -0.0234375, -0.0703125, 0.0625, 0.109375, 0.1015625, -0.0546875, -0.0078125, 0.046875, 0.015625, 0.0234375, 0.0625, -0.109375, -0.0625, 0.046875, -0.0390625, -0.1796875, -0.1015625, -0.046875, 0.2265625, 0.2421875, 0.1171875, -0.1484375, -0.1953125, -0.1015625, 0.015625, 0.1484375, 0.09375, 0.0859375, 0.0625, -0.0390625, -0.140625, -0.0859375, 0.0234375, -0.1328125, -0.0390625, 0.1171875, 0.1171875, 0.0546875, 0.09375, -0.03125, 0.0390625, 0.046875, 0.1015625, 0.0703125, -0.0078125, 0.015625, 0.015625, -0.0390625, -0.109375, -0.125, -0.1484375, 0.078125, 0.078125, 0.0859375, 0.046875, 0.03125, 0.0859375, -0.015625, -0.015625, -0.1171875, -0.0703125, 0.0546875, 0.0703125, 0.234375, 0.234375, 0.1015625, 0.0546875, 0.1171875, 0.109375, 0.03125, -0.0546875, -0.015625, -0.09375, -0.015625, -0.0234375, -0.0078125, -0.1015625, -0.1796875, -0.109375, -0.1171875, -0.1328125, -0.140625, -0.1484375, -0.0703125, -0.0234375, 0.0234375, -0.046875, -0.078125, 0.0078125, 0.03125, -0.1171875, -0.15625, 0.046875, 0.1328125, 0.03125, 0.109375, 0.03125, 0.09375, 0.0234375, -0.0546875, 0.109375, 0.125, -0.0703125, -0.0234375, -0.09375, -0.1484375, -0.03125, 0.0078125, 0.03125, -0.0625, -0.3671875, -0.34375, -0.3125, -0.3203125, -0.2890625, -0.2421875, -0.15625, -0.1328125, -0.203125, -0.1015625, -0.3046875, -0.328125, -0.21875, -0.03125, -0.109375, -0.265625, -0.265625, -0.0625, 0.0546875, 0.0234375, 0.1328125, 0.0390625, -0.09375, 0.1015625, 0.0078125, -0.0078125, 0.1015625, 0.046875, 0.2265625, 0.2109375, 0.1015625, 0.1484375, 0.09375, 0.046875, 0.2421875, 0.15625, 0.0234375, 0.0625, 0.171875, 0.15625, 0.2265625, 0.1328125, 0.0234375, -0.03125, -0.0390625, -0.0390625, -0.046875, -0.09375, -0.046875, 0.046875, 0.0390625, -0.1015625, 0.015625, 0.0390625, 0.0234375, 0.0234375, 0.1015625, 0.0390625, -0.1015625, -0.171875, -0.203125, -0.0703125, 0.1015625, 0.0234375, -0.0078125, 0.015625, 0.0625, 0.1796875, 0.1015625, 0.140625, 0.046875, 0.046875, 0.2734375, 0.0390625, 0.0625, 0.1875, 0.203125, 0.0546875, 0.09375, 0.2890625, 0.203125, 0.0859375, 0.21875, 0.2734375, 0.3125, 0.1875, 0.203125, 0.265625, 0.2109375, 0.296875, 0.2265625, 0.140625, 0.2734375, 0.2421875, 0.1640625, 0.3203125, 0.0703125, 0.125, 0.1328125, 0.171875, 0.265625, 0.171875, 0.2109375, 0.078125, 0.0078125, 0.0703125, -0.0546875, 0.0, 0.1796875, -0.03125, -0.09375, -0.1796875, 0.0, 0.0, -0.1640625, -0.1640625, -0.1640625, -0.03125, -0.09375, -0.171875, -0.1875, -0.3359375, -0.2109375, -0.1640625, -0.1953125, -0.265625, -0.265625, -0.234375, -0.1796875, -0.2109375, -0.1640625, -0.2109375, -0.1640625, -0.2421875, -0.3125, -0.1875, -0.3203125, -0.234375, -0.1796875, -0.1640625, -0.3203125, -0.1796875, 0.0, -0.078125, -0.078125, -0.046875, -0.21875, -0.28125, -0.140625, -0.0546875, 0.0390625, -0.1171875, -0.078125, -0.0859375, 0.0234375, 0.0234375, -0.109375, 0.0078125, -0.0078125, -0.078125, 0.03125, 0.109375, 0.0234375, 0.0234375, 0.0859375, 0.1484375, 0.03125, 0.0078125, 0.0703125, 0.125, -0.109375, 0.0, 0.09375, 0.0546875, 0.03125, 0.0078125, 0.1015625, 0.046875, 0.0546875, 0.0390625, 0.1328125, 0.1328125, 0.1328125, 0.0, -0.015625, -0.1015625, -0.0546875, 0.0625, -0.0859375, 0.0234375, -0.0546875, 0.015625, 0.1640625, 0.1484375, 0.046875, 0.1015625, 0.03125, -0.125, -0.0859375, -0.046875, 0.015625, 0.0234375, 0.1171875, 0.171875, 0.09375, -0.078125, -0.0703125, 0.0625, 0.09375, -0.046875, -0.0859375, 0.078125, 0.1796875, 0.1015625, 0.0234375, 0.015625, 0.1015625, 0.2578125, 0.1171875, 0.0234375, -0.015625, 0.0078125, 0.1015625, 0.0703125, 0.1640625, 0.203125, 0.1484375, 0.1328125, 0.109375, 0.15625, 0.25, 0.0234375, 0.125, 0.2109375, 0.1171875, 0.1171875, 0.234375, 0.1796875, 0.09375, 0.0, 0.15625, 0.15625, 0.0703125, 0.25, 0.125, 0.1328125, 0.046875, 0.09375, 0.2109375, 0.1796875, 0.0546875, 0.03125, 0.1171875, 0.2421875, 0.1484375, -0.0390625, -0.015625, 0.0234375, 0.09375, -0.0234375, 0.09375, 0.0703125, 0.015625, 0.0, -0.1171875, -0.078125, -0.0390625, 0.0390625, -0.125, -0.0546875, 0.0390625, 0.0078125, -0.140625, -0.203125, -0.1796875, -0.109375, -0.078125, -0.1484375, -0.2109375, -0.09375, -0.125, -0.1953125, -0.25, -0.2421875, -0.140625, -0.1640625, -0.1953125, -0.1796875, -0.3125, -0.203125, -0.2578125, -0.203125, -0.109375, -0.1484375, -0.2890625, -0.2265625, -0.2109375, -0.171875, -0.28125, -0.21875, -0.2421875, -0.28125, -0.1796875, -0.140625, -0.2265625, -0.1015625, -0.140625, -0.25, -0.34375, -0.234375, 0.0, -0.1328125, -0.0234375, 0.0, -0.0859375, -0.1171875, -0.171875, -0.0546875, -0.0546875, -0.109375, -0.03125, -0.1015625, -0.09375, -0.0703125, 0.046875, 0.1640625, 0.03125, 0.0625, -0.0078125, -0.015625, 0.171875, 0.046875, 0.03125, -0.046875, -0.0078125, 0.171875, 0.1875, 0.1953125, 0.046875, 0.21875, 0.234375, 0.15625, 0.125, 0.15625, 0.0859375, 0.2265625, 0.1875, 0.1796875, 0.1484375, 0.234375, 0.1796875, 0.1953125, 0.390625, 0.3203125, 0.234375, 0.1015625, 0.203125, 0.234375, 0.25, 0.1796875, 0.2265625, 0.265625, 0.2421875, 0.171875, 0.15625, 0.2109375, 0.1015625, 0.2578125, 0.2734375, 0.3203125, 0.2578125, 0.109375, 0.0625, 0.2109375, 0.203125, 0.1875, 0.1796875, 0.03125, 0.0859375, 0.125, 0.171875, 0.078125, 0.0234375, 0.1015625, 0.0703125, 0.0546875}, {-0.0078125, 0.0234375, -0.09375, -0.0703125, -0.0078125, -0.078125, 0.078125, 0.0859375, 0.109375, -0.0625, 0.0, 0.0390625, 0.0234375, 0.0390625, 0.0390625, -0.125, -0.03125, 0.0859375, -0.0859375, -0.171875, -0.125, 0.0, 0.1953125, 0.2734375, 0.0859375, -0.1484375, -0.21875, -0.0546875, 0.03125, 0.1484375, 0.0703125, 0.0390625, 0.0625, -0.0234375, -0.1015625, -0.109375, 0.0546875, -0.1328125, -0.046875, 0.078125, 0.0859375, 0.09375, 0.0078125, -0.0078125, 0.0703125, 0.03125, 0.0859375, 0.046875, 0.0, 0.0078125, 0.03125, -0.078125, -0.1171875, -0.1953125, -0.1015625, 0.0078125, 0.1171875, 0.0546875, 0.0546875, 0.0703125, 0.0390625, 0.0, -0.109375, -0.09375, -0.1015625, 0.0625, 0.09375, 0.1796875, 0.2421875, 0.1171875, 0.078125, 0.0625, 0.1640625, -0.0546875, 0.0546875, -0.03125, -0.078125, -0.0625, -0.0390625, -0.0078125, -0.1328125, -0.1640625, -0.140625, -0.1015625, -0.171875, -0.1796875, -0.1328125, -0.0703125, -0.078125, 0.046875, -0.0546875, -0.0546875, 0.0625, 0.0234375, 0.03125, -0.1484375, 0.1484375, 0.1796875, 0.0703125, 0.1328125, 0.109375, 0.1484375, 0.046875, 0.0234375, 0.171875, 0.203125, -0.0546875, 0.0078125, -0.0625, -0.0546875, -0.015625, 0.046875, 0.078125, -0.046875, -0.265625, -0.3359375, -0.2109375, -0.3046875, -0.203125, -0.1796875, -0.109375, -0.109375, -0.125, -0.09375, -0.2578125, -0.2890625, -0.1640625, 0.0, -0.0703125, -0.1640625, -0.2421875, 0.0, 0.078125, 0.0546875, 0.171875, 0.03125, -0.015625, 0.125, 0.0625, 0.0234375, 0.125, 0.0625, 0.21875, 0.2265625, 0.109375, 0.1640625, 0.109375, 0.09375, 0.2109375, 0.1953125, -0.046875, 0.1328125, 0.109375, 0.1640625, 0.1875, 0.1171875, 0.0078125, -0.0546875, -0.0859375, -0.0625, -0.1171875, -0.1015625, -0.1171875, 0.0078125, 0.0, -0.15625, -0.03125, -0.03125, -0.0234375, -0.03125, 0.0390625, -0.0390625, -0.15625, -0.2578125, -0.25, -0.1640625, 0.0625, -0.0859375, -0.0546875, -0.078125, -0.015625, 0.0859375, 0.015625, 0.0546875, -0.03125, -0.0234375, 0.1796875, -0.015625, -0.03125, 0.140625, 0.09375, 0.015625, -0.015625, 0.2421875, 0.1015625, 0.03125, 0.1328125, 0.2265625, 0.2265625, 0.140625, 0.140625, 0.21875, 0.1640625, 0.234375, 0.203125, 0.0625, 0.2734375, 0.1640625, 0.1796875, 0.25, 0.0859375, 0.0703125, 0.140625, 0.1328125, 0.265625, 0.1484375, 0.203125, 0.078125, -0.0078125, 0.09375, -0.078125, 0.0234375, 0.15625, 0.0, -0.1015625, -0.1484375, 0.0078125, 0.03125, -0.15625, -0.125, -0.1484375, 0.0078125, -0.0703125, -0.1328125, -0.1640625, -0.28125, -0.1953125, -0.1015625, -0.1875, -0.1796875, -0.2578125, -0.15625, -0.15625, -0.1484375, -0.109375, -0.1640625, -0.0859375, -0.2109375, -0.2265625, -0.171875, -0.2109375, -0.2265625, -0.0703125, -0.1484375, -0.21875, -0.1484375, 0.09375, -0.0390625, -0.015625, 0.03125, -0.1796875, -0.171875, -0.1328125, 0.0703125, 0.0390625, -0.015625, -0.0546875, -0.0078125, 0.0703125, 0.0703125, -0.0390625, 0.0390625, 0.078125, -0.0546875, 0.1171875, 0.125, 0.0859375, 0.0546875, 0.1328125, 0.1953125, 0.0546875, 0.0625, 0.0859375, 0.1640625, -0.0859375, 0.0234375, 0.1171875, 0.078125, 0.0390625, 0.0390625, 0.078125, 0.09375, 0.0078125, 0.09375, 0.0859375, 0.15625, 0.1015625, -0.0078125, -0.0234375, -0.1328125, -0.0390625, 0.0, -0.0703125, -0.0546875, -0.046875, -0.0625, 0.15625, 0.078125, 0.0234375, 0.03125, 0.0, -0.1875, -0.125, -0.1015625, -0.046875, -0.03125, 0.046875, 0.1171875, 0.015625, -0.1328125, -0.1484375, 0.0, 0.015625, -0.109375, -0.1640625, 0.0078125, 0.09375, 0.0390625, -0.0625, -0.0546875, 0.015625, 0.1953125, 0.03125, -0.03125, -0.109375, -0.0390625, 0.0, 0.0234375, 0.0703125, 0.140625, 0.078125, 0.0625, 0.046875, 0.09375, 0.1796875, -0.03125, 0.0625, 0.171875, 0.046875, 0.078125, 0.171875, 0.140625, 0.046875, -0.0390625, 0.1171875, 0.125, 0.0390625, 0.21875, 0.109375, 0.1015625, 0.0390625, 0.0546875, 0.21875, 0.1484375, 0.0625, 0.0078125, 0.125, 0.25, 0.1484375, -0.0234375, -0.015625, 0.0625, 0.09375, 0.015625, 0.109375, 0.109375, 0.0390625, 0.03125, -0.0703125, -0.046875, 0.0078125, 0.078125, -0.0859375, 0.0078125, 0.0703125, 0.0859375, -0.109375, -0.125, -0.1328125, -0.03125, -0.0234375, -0.078125, -0.1484375, -0.0234375, -0.0546875, -0.125, -0.1796875, -0.1640625, -0.078125, -0.0859375, -0.1328125, -0.109375, -0.2421875, -0.125, -0.1953125, -0.1328125, -0.046875, -0.078125, -0.2265625, -0.1640625, -0.140625, -0.125, -0.1875, -0.1953125, -0.140625, -0.265625, -0.09375, -0.109375, -0.15625, -0.0703125, -0.0859375, -0.2109375, -0.3046875, -0.1796875, 0.015625, -0.0703125, -0.0234375, 0.0546875, -0.0859375, -0.078125, -0.1640625, -0.0234375, -0.0546875, -0.09375, -0.03125, -0.09375, -0.09375, -0.0703125, 0.03125, 0.1640625, 0.0078125, 0.0625, -0.03125, -0.03125, 0.1484375, 0.0234375, 0.0, -0.0703125, -0.0390625, 0.1328125, 0.1640625, 0.1484375, 0.015625, 0.1640625, 0.1875, 0.1015625, 0.0703125, 0.09375, 0.03125, 0.1640625, 0.1328125, 0.1171875, 0.0859375, 0.171875, 0.1015625, 0.1484375, 0.296875, 0.28125, 0.125, 0.0859375, 0.0859375, 0.203125, 0.1484375, 0.140625, 0.140625, 0.203125, 0.171875, 0.09375, 0.1015625, 0.125, 0.0625, 0.15625, 0.2421875, 0.21875, 0.2265625, 0.015625, 0.03125, 0.1328125, 0.171875, 0.125, 0.140625, -0.0234375, 0.046875, 0.0703125, 0.1328125, 0.03125, -0.015625, 0.0703125, 0.0390625, 0.0234375}};

}; // end namespace