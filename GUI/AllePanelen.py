from tkinter import *

alle_panelen = Tk()
alle_panelen.title("Alle panelen")
alle_panelen.geometry("800x500+600+250")

alles = Frame(alle_panelen)
alles.pack(anchor=NW)
tkvar = StringVar(alle_panelen)
tkvar1 = StringVar(alle_panelen)
#  ********************LABELS*******************
#  ********************NAAM + INFO*******************
alles_name = Label(alles, text="Alle panelen")
alles_name.grid(row=0, columnspan=2, sticky=W)
alles_name.grid_configure(padx=(40,0), pady=(20,0))

alles_info = Label(alles, text="De bediening geldt voor alle zonnepanelen")
alles_info.grid(row=1, columnspan=3, sticky=W)
alles_info.grid_configure(padx=(15,0))

#  ********************GEMIDDELDE TEMP + LICHT*******************
alles_gtemp = Label(alles, text="Gemiddelde temperatuur")
alles_gtemp.grid(row=2, columnspan=2, sticky=W)
alles_gtemp.grid_configure(padx=(15,15))

alles_glicht = Label(alles, text="Gemiddelde lichtintensiteit")
alles_glicht.grid(row=2, column=4, columnspan=2, sticky=W)
alles_glicht.grid_configure(padx=(15,0))

#  ********************PANELEN + TIJD (TEMP)*******************
alles_temp_panelen = Label(alles, text="Panelen")
alles_temp_panelen.grid(row=4, sticky=W)
alles_temp_panelen.grid_configure(padx=(15,0))

alles_temp_tijd = Label(alles, text="Tijd")
alles_temp_tijd.grid(row=5, sticky=W)
alles_temp_tijd.grid_configure(padx=(15,0))

alles_temp_panelen1 = Label(alles, text="Panelen")
alles_temp_panelen1.grid(row=4, column=4, sticky=W)
alles_temp_panelen1.grid_configure(padx=(15,0))

alles_temp_tijd1 = Label(alles, text="Tijd")
alles_temp_tijd1.grid(row=5, column=4, sticky=W)
alles_temp_tijd1.grid_configure(padx=(15,0))

#  ********************DROP DOWN MENU'S*******************
choices_panelenP = {'Zonnescherm 1', 'Zonnescherm 2', 'Zonnescherm 3', 'Alle zonneschermen'}
choices_panelenT = {'Zonnescherm 1', 'Zonnescherm 2', 'Zonnescherm 3', 'Alle zonneschermen'}
tkvar.set('Alle zonneschermen')
popupMenuP = OptionMenu(alles, tkvar, *choices_panelenP)
popupMenuP.config(width=45)
popupMenuP.grid(row=4, column=1, columnspan=3, sticky=E)

choices_tijdP = {'Tijd 0', 'Tijd 1', 'Tijd 2', 'Tijd 3'}
choices_tijdT = {'Tijd 0', 'Tijd 1', 'Tijd 2', 'Tijd 3'}
tkvar1.set('Alle tijden')
popupMenuT = OptionMenu(alles, tkvar1, *choices_tijdP)
popupMenuT.config(width=45)
popupMenuT.grid(row=5, column=1, columnspan=3, sticky=E)

popupMenuP1 = OptionMenu(alles, tkvar, *choices_panelenT)
popupMenuP1.config(width=45)
popupMenuP1.grid(row=4, column=5, columnspan=3, sticky=E)

popupMenuT1 = OptionMenu(alles, tkvar1, *choices_tijdT)
popupMenuT1.config(width=45)
popupMenuT1.grid(row=5, column=5, columnspan=3, sticky=E)


#  ********************BUTTONS*******************
#  ********************UITROL & INROL BUTTON*******************
alles_button_uitrol = Button(alles, text="Uitrollen")
alles_button_uitrol.config(width=10)
alles_button_uitrol.grid(row=6, column=0)
alles_button_uitrol.grid_configure(padx=(10, 0))

alles_button_inrol = Button(alles, text="Inrollen")
alles_button_inrol.config(width=10)
alles_button_inrol.grid(row=6, column=1)
alles_button_inrol.grid_configure(padx=(0, 15))

#  ********************+10(CM) & -10(CM)*******************
alles_button_plus = Button(alles, text="+ 10(cm)")
alles_button_plus.config(width=10)
alles_button_plus.grid(row=7, column=0)
alles_button_plus.grid_configure(padx=(10, 0))

alles_button_minus = Button(alles, text="- 10(cm)")
alles_button_minus.config(width=10)
alles_button_minus.grid(row=7, column=1)
alles_button_minus.grid_configure(padx=(0, 15))

#  ********************AUTOMATISCH & HANDMATIG + INSTELLINGEN*******************
alles_button_auto = Button(alles, text="Automatisch")
alles_button_auto.config(width=12)
alles_button_auto.grid(row=6, column=2)
alles_button_auto.grid_configure(padx=(15, 0))

alles_button_hand = Button(alles, text="Handmatig")
alles_button_hand.config(width=12)
alles_button_hand.grid(row=6, column=3)

alles_button_sett = Button(alles, text="Instellingen")
alles_button_sett.config(width=26)
alles_button_sett.grid(row=7, column=2, columnspan=2)
alles_button_sett.grid_configure(padx=(15, 0))


alle_panelen.mainloop()
