#include <Tone.h>
#include <TimerOne.h>

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

Tone tonePlayer;
Song currentSong;
int bpm = 400; // song tempo in eighth notes

void setup() {
  currentSong.notes = new Note[16]
  {
    {NOTE_A5, 1},
    {0, 1},
    {NOTE_E5, 1},
    {NOTE_D5, 1},
    {NOTE_CS5, 2},
    {0, 1},
    {NOTE_CS5, 1},
    {NOTE_D5, 1},
    {NOTE_E5, 1},
    {NOTE_FS5, 1},
    {NOTE_GS5, 1},
    {NOTE_E5, 2},
    {0, 2}
  };
  currentSong.notesLength = 16;
  currentSong.currentNote = 0;
  
  tonePlayer.begin(BUZZ_PIN);

  Timer1.initialize(60000000/bpm); // timer set to eighth notes in µs
  Timer1.attachInterrupt(playSong);

  Serial.begin(9600);
}

void loop() {
  Serial.println(currentSong.notes[currentSong.currentNote].frequency);
}

void playSong()
{
  if (currentSong.notesLength <= currentSong.currentNote) //return;
  {
    currentSong.notes = new Note[16]
    {
      {NOTE_A5, 1},
      {0, 1},
      {NOTE_E5, 1},
      {NOTE_D5, 1},
      {NOTE_CS5, 2},
      {0, 1},
      {NOTE_CS5, 1},
      {NOTE_D5, 1},
      {NOTE_E5, 1},
      {NOTE_FS5, 1},
      {NOTE_GS5, 1},
      {NOTE_E5, 2},
      {0, 2}
    };
    currentSong.notesLength = 16;
    currentSong.currentNote = 0;
  }

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