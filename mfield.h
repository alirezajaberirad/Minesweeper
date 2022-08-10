/*#ifndef MFIELD_H
#define MFIELD_H


class MField
{
public:
    MField(int numOfM);
private:
    class Tile{
    public:
        enum class State{
            Hidden,
            Flagged,
            Revealed
        };
        void landM();
        bool HasM() const;
    private:
        State state=State::Hidden;
        bool hasM=false;
    };
    const int width=30;
    const int height=16;
    Tile field[width*height];
};

#endif // MFIELD_H
*/
