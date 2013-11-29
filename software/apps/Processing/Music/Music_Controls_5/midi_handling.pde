void noteOnReceived(Note note) {
  
  byte channel = byte(note.getChannel());
  byte pitch = byte(note.getPitch());
  byte velocity = byte(note.getVelocity());

  output.sendNoteOn(channel, pitch, velocity);  
}

void noteOffReceived(Note note) {

  byte channel = byte(note.getChannel());
  byte pitch = byte(note.getPitch());
  byte velocity = byte(note.getVelocity());
  
  output.sendNoteOff(channel, pitch, velocity);
}

void controllerChangeReceived(rwmidi.Controller controller) {
  
  byte channel = byte(controller.getChannel());
  byte CC = byte(controller.getCC());
  byte value = byte(controller.getValue());
  
  output.sendController(channel, CC, value);
}
