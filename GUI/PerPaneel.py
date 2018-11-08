from tkinter import *


per_paneel = Tk()
per_paneel.title("Per paneel")
per_paneel.geometry("800x500+600+250")

zonnescherm_1 = Frame(per_paneel)
zonnescherm_1.pack(anchor=NW)
#  ********************LABELS*******************
#  ********************NAAM + LOCATIE*******************
name = Label(zonnescherm_1, text="Zonnescherm 1")
name.grid(row=0, columnspan=2, sticky=W)
name.grid_configure(padx=(40,0), pady=(20,0))

location = Label(zonnescherm_1, text="Locatie:  " + "ZP11/D150")
location.grid(row=1, columnspan=2, sticky=W)
location.grid_configure(padx=(40,0))

#  ********************GEMIDDELDE TEMP + LICHT*******************
gtemp = Label(zonnescherm_1, text="Gemiddelde temperatuur")
gtemp.grid(row=2, columnspan=2, sticky=W+E)
gtemp.grid_configure(padx=(15,15))

glicht = Label(zonnescherm_1, text="Gemiddelde lichtintensiteit")
glicht.grid(row=2, column=2, columnspan=2, sticky=W+E)
glicht.grid_configure(padx=(15,0))

#  ********************STATUS(VALUE) & AFSTAND(VALUE)*******************
status = Label(zonnescherm_1, text="Status:")
status.grid(row=4, column=0, sticky=W)
status.grid_configure(padx=(15,0))
svalue = Label(zonnescherm_1, text="Uitgerold")
svalue.grid(row=4, column=1, sticky=E)
svalue.grid_configure(padx=(0, 15))

afstand = Label(zonnescherm_1, text="Afstand:")
afstand.grid(row=5, column=0, sticky=W)
afstand.grid_configure(padx=(15,0))
avalue = Label(zonnescherm_1, text="1.60(CM)")
avalue.grid(row=5, column=1, sticky=E)
avalue.grid_configure(padx=(0,15))

#  ********************TEMP(VALUE) & LICHT(VALUE)*******************
temp = Label(zonnescherm_1, text="Temperatuur:")
temp.grid(row=4, column=2, sticky=W)
temp.grid_configure(padx=(15, 0))
tvalue = Label(zonnescherm_1, text="22.3")
tvalue.grid(row=4, column=3, sticky=E)

licht = Label(zonnescherm_1, text="Afstand:")
licht.grid(row=5, column=2, sticky=W)
licht.grid_configure(padx=(15,0))
lvalue = Label(zonnescherm_1, text="0.323")
lvalue.grid(row=5, column=3, sticky=E)

#  ********************BUTTONS*******************
#  ********************UITROL & INROL BUTTON*******************
button_uitrol = Button(zonnescherm_1, text="Uitrollen")
button_uitrol.config(width=10)
button_uitrol.grid(row=6, column=0)
button_uitrol.grid_configure(padx=(10, 0))

button_inrol = Button(zonnescherm_1, text="Inrollen")
button_inrol.config(width=10)
button_inrol.grid(row=6, column=1)
button_inrol.grid_configure(padx=(0, 15))

#  ********************+10(CM) & -10(CM)*******************
button_plus = Button(zonnescherm_1, text="+ 10(cm)")
button_plus.config(width=10)
button_plus.grid(row=7, column=0)
button_plus.grid_configure(padx=(10, 0))

button_minus = Button(zonnescherm_1, text="- 10(cm)")
button_minus.config(width=10)
button_minus.grid(row=7, column=1)
button_minus.grid_configure(padx=(0, 15))

#  ********************AUTOMATISCH & HANDMATIG + INSTELLINGEN*******************
button_auto = Button(zonnescherm_1, text="Automatisch")
button_auto.config(width=12)
button_auto.grid(row=6, column=2)
button_auto.grid_configure(padx=(15, 0))

button_hand = Button(zonnescherm_1, text="Handmatig")
button_hand.config(width=12)
button_hand.grid(row=6, column=3)

button_sett = Button(zonnescherm_1, text="Instellingen")
button_sett.config(width=26)
button_sett.grid(row=7, column=2, columnspan=2)
button_sett.grid_configure(padx=(15, 0))

per_paneel.mainloop()