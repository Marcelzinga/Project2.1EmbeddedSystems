from tkinter import*

A_wijzigingen = Tk()
A_wijzigingen.title("Wijzigingen")
A_wijzigingen.geometry("800x500+600+250")

wijzigingen = Frame(A_wijzigingen)
wijzigingen.pack(anchor=NW, side=LEFT)

F2 = Frame(A_wijzigingen)
F2.pack(anchor=NE, side=LEFT)
Infovar = StringVar(F2)

wijzigingen_name = Label(wijzigingen, text="Wijzigingen")
wijzigingen_name.grid(sticky=W)
wijzigingen_name.grid_configure(padx=(15,0), pady=(15,15))
#*********************EXTRA INFO*******************
IL1 = Label(F2, text="Extra Informatie")
IL1.grid(sticky=W)
IL1.grid_configure(padx=25, pady=(50,0))

I1 = Message(F2, textvariable=Infovar)
I1.grid(row=1, columnspan=2, sticky= W)
I1.grid_configure(padx=(15, 0))
I1.config(width=300)
Infovar.set("Dit is nog wat extra tekst wat je zou verwachten bij wat extra informatie?")





#*********************BUTTON COMMANDS*******************
E1var = StringVar()
E2var = StringVar()
E3var = StringVar()
E4var = StringVar()
E5var = StringVar()
E6var = StringVar()
E7var = StringVar()

def opslaan():
    print(E1var.get())
    print(E2var.get())
    print(E3var.get())
    print(E4var.get())
    print(E5var.get())
    print(E6var.get())
    print(E7var.get())
    print(char)


L1 = Label(wijzigingen, text="Naam")
L1.grid(row=1, columnspan=2, sticky=W)
L1.grid_configure(padx=(15,0))
E1var.set("Hallo")
E1 = Entry(wijzigingen, textvariable=E1var)
E1.grid(row=1, column=2, sticky=E)

L2 = Label(wijzigingen, text="Locatie")
L2.grid(row=2, columnspan=2, sticky=W)
L2.grid_configure(padx=(15,0))
E2 = Entry(wijzigingen, textvariable=E2var)
E2.grid(row=2, column=2, sticky=W)

L3 = Label(wijzigingen, text="Maximale uitrol")
L3.grid(row=3, columnspan=2, sticky=W)
L3.grid_configure(padx=(15,0))
E3 = Entry(wijzigingen, textvariable=E3var)
E3.grid(row=3, column=2, sticky=W)

L4 = Label(wijzigingen, text="Maximale inrol")
L4.grid(row=4, columnspan=2, sticky=W)
L4.grid_configure(padx=(15,0))
E4 = Entry(wijzigingen, textvariable=E4var)
E4.grid(row=4, column=2, sticky=W)

L5 = Label(wijzigingen, text="Maximale lichtintensiteit")
L5.grid(row=5, columnspan=2, sticky=W)
L5.grid_configure(padx=(15,0))
E5 = Entry(wijzigingen, textvariable=E5var)
E5.grid(row=5, column=2, sticky=W)

L6 = Label(wijzigingen, text="Minimale lichtintensiteit")
L6.grid(row=6, columnspan=2, sticky=W)
L6.grid_configure(padx=(15,0))
E6 = Entry(wijzigingen, textvariable=E6var)
E6.grid(row=6, column=2, sticky=W)

L7 = Label(wijzigingen, text="Maximale temperatuur")
L7.grid(row=7, columnspan=2, sticky=W)
L7.grid_configure(padx=(15,0))
E7 = Entry(wijzigingen)
E7.grid(row=7, column=2, sticky=W)

L8 = Label(wijzigingen, text="Minimale temperatuur")
L8.grid(row=8, columnspan=2, sticky=W)
L8.grid_configure(padx=(15,0))
E8 = Entry(wijzigingen, textvariable=E7var)
E8.grid(row=8, column=2, sticky=W)

B1 = Button(wijzigingen, text="Opslaan", command=opslaan)
B1.grid(row=9, sticky=W)
B1.grid_configure(padx=(15,0), pady=(10,0))

B2 = Button(wijzigingen, text="Anuleren", command=quit)
B2.grid(row=9, column =2, sticky=W)
B2.grid_configure(pady=(10,0))

wijzigingen.mainloop()