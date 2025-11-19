#include <Tone.h>
#include <TimerOne.h>

#define SEASHANTY2_LENGTH 149
#define BUZZ_PIN 2

struct Note
{
  int frequency;
  int duration;
};

struct Song
{
  Note* notes;
  int notesLength;
  int currentNote;
};

Note* seaShanty2;

Tone tonePlayer;
Song currentSong;
int bpm = 400; // song tempo in sixteenth notes

void setup() {
  initSongs();
  setSong(seaShanty2, SEASHANTY2_LENGTH);
  tonePlayer.begin(BUZZ_PIN);

  Timer1.initialize(60000000/bpm); // timer set to sixteenth notes in µs
  Timer1.attachInterrupt(playSong);

  Serial.begin(9600);
}

void loop() {
  if (currentSong.notesLength <= currentSong.currentNote)
  {
    setSong(seaShanty2, SEASHANTY2_LENGTH);
  }
}

void playSong()
{
  if (currentSong.notesLength <= currentSong.currentNote) return;

  Note* targetNote = &currentSong.notes[currentSong.currentNote];

  if (targetNote->duration <= 0)
  {
    currentSong.currentNote++;
    targetNote = &currentSong.notes[currentSong.currentNote];
  }

  if (currentSong.currentNote < currentSong.notesLength)
  {
    if (targetNote-> frequency == 0)
    {
      tonePlayer.stop();
    }
    else
    {
      tonePlayer.play(targetNote->frequency);
    }
    
    targetNote->duration--;
  }
}

void setSong(Note* _song, int _songLength)
{
  currentSong.currentNote = 0;
  currentSong.notesLength = _songLength;
  currentSong.notes = new Note[_songLength];

  for (int i = 0; i < _songLength; i++)
  {
    currentSong.notes[i] = {_song[i].frequency, _song[i].duration};
  }
}