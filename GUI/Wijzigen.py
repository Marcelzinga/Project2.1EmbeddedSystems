from tkinter import*

wijzigingen = Tk()
wijzigingen.title("Wijzigingen")
wijzigingen.geometry("800x500+600+250")

wijzigingen_name = Label(wijzigingen, text="Wijzigingen")
wijzigingen_name.grid(sticky=W)
wijzigingen_name.grid_configure(padx=(15,0), pady=(15,15))

L1 = Label(wijzigingen, text="Naam")
L1.grid(row=1, columnspan=2, sticky=W)
L1.grid_configure(padx=(15,0))
E1 = Entry(wijzigingen)
E1.grid(row=1, column=2, sticky=W)

L2 = Label(wijzigingen, text="Locatie")
L2.grid(row=2, columnspan=2, sticky=W)
L2.grid_configure(padx=(15,0))
E2 = Entry(wijzigingen)
E2.grid(row=2, column=2, sticky=W)

L3 = Label(wijzigingen, text="Maximale uitrol")
L3.grid(row=3, columnspan=2, sticky=W)
L3.grid_configure(padx=(15,0))
E3 = Entry(wijzigingen)
E3.grid(row=3, column=2, sticky=W)

L4 = Label(wijzigingen, text="Maximale inrol")
L4.grid(row=4, columnspan=2, sticky=W)
L4.grid_configure(padx=(15,0))
E4 = Entry(wijzigingen)
E4.grid(row=4, column=2, sticky=W)

L5 = Label(wijzigingen, text="Maximale lichtintensiteit")
L5.grid(row=5, columnspan=2, sticky=W)
L5.grid_configure(padx=(15,0))
E5 = Entry(wijzigingen)
E5.grid(row=5, column=2, sticky=W)

L6 = Label(wijzigingen, text="Minimale lichtintensiteit")
L6.grid(row=6, columnspan=2, sticky=W)
L6.grid_configure(padx=(15,0))
E6 = Entry(wijzigingen)
E6.grid(row=6, column=2, sticky=W)

L7 = Label(wijzigingen, text="Maximale temperatuur")
L7.grid(row=7, columnspan=2, sticky=W)
L7.grid_configure(padx=(15,0))
E7 = Entry(wijzigingen)
E7.grid(row=7, column=2, sticky=W)

L8 = Label(wijzigingen, text="Minimale temperatuur")
L8.grid(row=8, columnspan=2, sticky=W)
L8.grid_configure(padx=(15,0))
E8 = Entry(wijzigingen)
E8.grid(row=8, column=2, sticky=W)

B1 = Button(wijzigingen, text="Opslaan")
B1.grid(row=9, sticky=W)
B1.grid_configure(padx=(15,0), pady=(10,0))

B2 = Button(wijzigingen, text="Anuleren")
B2.grid(row=9, column =2, sticky=W)
B2.grid_configure(pady=(10,0))

wijzigingen.mainloop()