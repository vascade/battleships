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

void playAlarm()
{
  for (
    int j = ALARM_START; 
    j <= ALARM_END;
    j++)
  {
    tonePlayer.play(j);
    delay(10);
  }

  tonePlayer.stop();
}

void playHit()
{
  for (int j = 0; j < 100; j++)
  {
    tonePlayer.play(random(NOTE_C2-j, NOTE_C3-j));
    delay(50);
  }

  tonePlayer.stop();
}

void playMiss()
{
  tonePlayer.play(NOTE_C3, 100);
  delay(100);
  tonePlayer.play(NOTE_C2, 100);
  delay(100);
}