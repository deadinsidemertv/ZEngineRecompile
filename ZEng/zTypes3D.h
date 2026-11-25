class zColor {
public:
    unsigned int rgba;

    zColor(unsigned int v) : rgba(v) {}
    zColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
        : rgba(b | (g << 8) | (r << 16) | (a << 24)) {
    }
};