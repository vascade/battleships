void LCDClearPrint(LiquidCrystal lcd, String message)
{
  lcd.noBlink();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}
