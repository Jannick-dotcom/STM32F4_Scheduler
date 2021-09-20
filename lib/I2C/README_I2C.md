## **Stallardo Operating System**
**StallardOS_I2C**


Funktionen Erklärung:

```
StallardOSi2c::StallardOSi2c(I2C_TypeDef *instance, uint32_t freq)
```
erzeugt einen I2C Instance.

Funktion Parameter:
```
instance -> I2C zu verwenden
freq     -> Frequenz der Übertragung
```

```
StallardOSi2c::write(uint16_t addr, uint8_t *data, uint16_t bytes)
```

Senden von I2C Data.

Funktion Parameter:
```
addr  -> zu welche Adresse schicken wir unsere Nachricht
data  -> Data zu senden
bytes -> Große der Data Container
```


```
StallardOSi2c::read(uint16_t addr, uint8_t *data, uint16_t bytes)
```

Empfangen von I2C Data.

Funktion Parameter:
```
addr   -> von welche Adresse empfangen wir unsere Nachricht
data   -> Data zu empfangen
bytes  -> Große der Data Container
return -> Wenn Data Empfangen wurde = True, sonnst False (Boolean)
```