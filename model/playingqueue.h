#ifndef PLAYINGQUEUE_H
#define PLAYINGQUEUE_H

#include <QQueue>
#include "track.h"

class PlayingQueue : public QQueue<Track*>
{

public:    
    explicit PlayingQueue();

};

#endif // PLAYINGQUEUE_H
