from tkinter import*
import tkinter.messagebox

def warning():
    answer = tkinter.messagebox.askquestion("WAARSCHUWING", "Weet u zeker dat u Zonnescherm ? wilt verwijderen?")
    if answer == "yes":
        print("Scherm is verwijderd")
    if answer == "no":
        print("Scherm is niet verwijderd")
instellingen = Tk()
instellingen.title("Instellingen")
instellingen.geometry("800x500+600+250")

var = StringVar()
var1 = StringVar()
settings = Frame(instellingen)
settings.pack(anchor=NW)

alles_name = Label(settings, text="Instellingen")
alles_name.grid(row=0, columnspan=2, sticky=W)
alles_name.grid_configure(padx=(15, 0),pady=(15,5))

instel_label = Message(settings, textvariable=var)
instel_label.grid(row=1, columnspan=2, sticky= W)
instel_label.grid_configure(padx=(15, 0))
instel_label.config(width=300)
var.set("Dit is nog wat extra tekst wat je zou verwachten bij een instellingen panel?")

alles_name1 = Label(settings, text="Algemene Instellingen")
alles_name1.grid(row=2, columnspan=2, sticky=W)
alles_name1.grid_configure(padx=(15,0),pady=(25,5))

instel_label = Message(settings, textvariable=var1)
instel_label.grid (row=3, columnspan=2, sticky= W)
instel_label.grid_configure(padx=(15, 0))
instel_label.config(width=300)
var1.set("Dit is nog wat extra tekst wat je zou verwachten bij een algemene instellingen panel!!!!!!")

per_zonnescherm = Label(settings, text="Per Zonnescherm")
per_zonnescherm.grid(row=4, sticky=W)
per_zonnescherm.grid_configure(padx=(15,0), pady=(25,10))
#  ********************NAMEN ZONNESCHERM*******************

per_zonnescherm_naam = Label(settings, text="Naam", relief=RIDGE)
per_zonnescherm_naam.grid(row=5, sticky=W)
per_zonnescherm_naam.config(width=30)
per_zonnescherm_naam.grid_configure(padx=(20,0))

per_zonnescherm_naam1 = Label(settings, text="Zonnescherm 1", relief=SUNKEN)
per_zonnescherm_naam1.grid(row=6, sticky=W)
per_zonnescherm_naam1.config(width=30)
per_zonnescherm_naam1.grid_configure(padx=(20,0))

per_zonnescherm_naam2 = Label(settings, text="Zonnescherm 2", relief=RIDGE)
per_zonnescherm_naam2.grid(row=7, sticky=W)
per_zonnescherm_naam2.config(width=30)
per_zonnescherm_naam2.grid_configure(padx=(20,0))

per_zonnescherm_naam3 = Label(settings, text="Zonnescherm 3", relief=SUNKEN)
per_zonnescherm_naam3.grid(row=8, sticky=W)
per_zonnescherm_naam3.config(width=30)
per_zonnescherm_naam3.grid_configure(padx=(20,0))

per_zonnescherm_naam4 = Label(settings, text="Zonnescherm 4", relief=RIDGE)
per_zonnescherm_naam4.grid(row=9, sticky=W)
per_zonnescherm_naam4.config(width=30)
per_zonnescherm_naam4.grid_configure(padx=(20,0))

#  ********************LOCATIE ZONNESCHERM*******************

per_zonnescherm_locatie = Label(settings, text="Locatie", relief=SUNKEN)
per_zonnescherm_locatie.grid(row=5, column=1, sticky=W)
per_zonnescherm_locatie.config(width=30)

per_zonnescherm_locatie1 = Label(settings, text="ZP11/D150", relief=RIDGE)
per_zonnescherm_locatie1.grid(row=6, column=1, sticky=W)
per_zonnescherm_locatie1.config(width=30)

per_zonnescherm_locatie2 = Label(settings, text="ZP11/D151", relief=RIDGE)
per_zonnescherm_locatie2.grid(row=7, column=1, sticky=W)
per_zonnescherm_locatie2.config(width=30)

per_zonnescherm_locatie3 = Label(settings, text="ZP11/D152", relief=RIDGE)
per_zonnescherm_locatie3.grid(row=8, column=1, sticky=W)
per_zonnescherm_locatie3.config(width=30)

per_zonnescherm_locatie4 = Label(settings, text="ZP11/D153", relief=RIDGE)
per_zonnescherm_locatie4.grid(row=9, column=1, sticky=W)
per_zonnescherm_locatie4.config(width=30)

#  ********************ACTIE ZONNESCHERM*******************

per_zonnescherm_actie = Label(settings, text="Actie", relief=RIDGE)
per_zonnescherm_actie.grid(row=5, column=2, columnspan=2, sticky=W)
per_zonnescherm_actie.config(width=42)

per_zonnescherm_actie4 = Button(settings, text="Wijzigen")
per_zonnescherm_actie4.grid(row=6, column=2, sticky=W)
per_zonnescherm_actie4.config(width=20)

per_zonnescherm_actie1 = Button(settings, text="Wijzigen")
per_zonnescherm_actie1.grid(row=7, column=2, sticky=W)
per_zonnescherm_actie1.config(width=20)

per_zonnescherm_actie2 = Button(settings, text="Wijzigen")
per_zonnescherm_actie2.grid(row=8, column=2, sticky=W)
per_zonnescherm_actie2.config(width=20)

per_zonnescherm_actie3 = Button(settings, text="Wijzigen")
per_zonnescherm_actie3.grid(row=9, column=2, sticky=W)
per_zonnescherm_actie3.config(width=20)

per_zonnescherm_verwijder = Button(settings, text="Verwijderen", command=warning)
per_zonnescherm_verwijder.grid(row=6, column=3, sticky=W)
per_zonnescherm_verwijder.config(width=20)

per_zonnescherm_verwijder1 = Button(settings, text="Verwijderen", command=warning)
per_zonnescherm_verwijder1.grid(row=7, column=3, sticky=W)
per_zonnescherm_verwijder1.config(width=20)

per_zonnescherm_verwijder2 = Button(settings, text="Verwijderen", command=warning)
per_zonnescherm_verwijder2.grid(row=8, column=3, sticky=W)
per_zonnescherm_verwijder2.config(width=20)

per_zonnescherm_verwijder3 = Button(settings, text="Verwijderen", command=warning)
per_zonnescherm_verwijder3.grid(row=9, column=3, sticky=W)
per_zonnescherm_verwijder3.config(width=20)

instellingen.mainloop()