import tkinter as tk  # python3
import serial, time, re
import _thread


TITLE_FONT = ("Helvetica", 18, "bold")

ser = serial.Serial('COM4', 19200, timeout=1)
print(ser)

class SampleApp(tk.Tk):

    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)

        # the container is where we'll stack a bunch of frames
        # on top of each other, then the one we want visible
        # will be raised above the others
        container = tk.Frame(self)
        container.pack(side="top", fill="both", expand=True)
        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)

        self.frames = {}
        for F, geometry in zip((PerPaneel, AllePanelen, Instellingen, Wijzigen),
                               ('900x700', '1000x700', '1000x700', '800x800')):
            page_name = F.__name__
            frame = F(parent=container, controller=self)
            # store the frame and the geometry for this frame
            self.frames[page_name] = (frame, geometry)

            # put all of the pages in the same location;
            # the one on the top of the stacking order
            # will be the one that is visible.
            frame.grid(row=0, column=1, sticky="nsew")

        self.show_frame("PerPaneel")

    def show_frame(self, page_name):
        '''Show a frame for the given page name'''
        frame, geometry = self.frames[page_name]
        # change geometry of the window
        self.update_idletasks()
        self.geometry(geometry)
        frame.tkraise()

    def show_frame1(self, page_name):
        '''Show a frame for the given page name'''
        frame, geometry = self.frames[page_name]
        # change geometry of the window
        self.update_idletasks()
        self.geometry(geometry)
        frame.tkraise()

class PerPaneel(tk.Frame):

    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.controller = controller

        f1 = tk.Frame(self)
        f1.grid(row=0, column=1)

        f2 = tk.Frame(self)
        f2.grid(row=0, column=0)
        f2.grid_anchor('nw')
        self.TempValue = tk.StringVar()
        self.LightValue = tk.StringVar()
        self.NameValue = tk.StringVar()
        self.DistanceValue = tk.StringVar()

        #  ****************************************************ZONNESCHERM1**************************************************************
        p1_perL1 = tk.Label(self, textvariable=self.NameValue)
        p1_perL1.grid(row=0, columnspan=2, column=1, sticky="W")
        p1_perL1.grid_configure(padx=(40, 0), pady=(20, 0))

        p1_perL2 = tk.Label(self, text="Locatie:  " + "ZP11/D150")
        p1_perL2.grid(row=1, columnspan=2, column=1, sticky="W")
        p1_perL2.grid_configure(padx=(40, 0))

        #  ********************GEMIDDELDE TEMP + LICHT*******************
        p1_perL3 = tk.Label(self, text="Gemiddelde temperatuur")
        p1_perL3.grid(row=2, columnspan=2, column=1, sticky="WE")
        p1_perL3.grid_configure(padx=(15, 15))

        p1_perL4 = tk.Label(self, text="Gemiddelde lichtintensiteit")
        p1_perL4.grid(row=2, column=3, columnspan=2, sticky="WE")
        p1_perL4.grid_configure(padx=(15, 0))

        #  ********************STATUS(VALUE) & AFSTAND(VALUE)*******************
        p1_perL5 = tk.Label(self, text="Status:")
        p1_perL5.grid(row=4, column=1, sticky="W")
        p1_perL5.grid_configure(padx=(15, 0))
        p1_perL6 = tk.Label(self, text="test")
        p1_perL6.grid(row=4, column=2, sticky="E")
        p1_perL6.grid_configure(padx=(0, 15))

        p1_perL7 = tk.Label(self, text="Afstand:")
        p1_perL7.grid(row=5, column=1, sticky="W")
        p1_perL7.grid_configure(padx=(15, 0))
        p1_perL8 = tk.Label(self, textvariable=self.DistanceValue)
        p1_perL8.grid(row=5, column=2, sticky="E")
        p1_perL8.grid_configure(padx=(0, 15))

        #  ********************TEMP(VALUE) & LICHT(VALUE)*******************
        p1_perL9 = tk.Label(self, text="Temperatuur:")
        p1_perL9.grid(row=4, column=3, sticky="W")
        p1_perL9.grid_configure(padx=(15, 0))
        p1_perL10 = tk.Label(self, textvariable=self.TempValue)
        p1_perL10.grid(row=4, column=4, sticky="E")

        p1_perL11 = tk.Label(self, text="Lichtintensiteit:")
        p1_perL11.grid(row=5, column=3, sticky="W")
        p1_perL11.grid_configure(padx=(15, 0))
        p1_perL12 = tk.Label(self, textvariable=self.LightValue)
        p1_perL12.grid(row=5, column=4, sticky="E")

        #  ********************tk.ButtonS*******************
        #  ********************UITROL & INROL tk.Button*******************
        p1_perB1 = tk.Button(self, text="Uitrollen")
        p1_perB1.config(width=10)
        p1_perB1.grid(row=6, column=1)
        p1_perB1.grid_configure(padx=(10, 0))

        p1_perB2 = tk.Button(self, text="Inrollen")
        p1_perB2.config(width=10)
        p1_perB2.grid(row=6, column=2)
        p1_perB2.grid_configure(padx=(0, 15))

        #  ********************+10(CM) & -10(CM)*******************
        p1_perB3 = tk.Button(self, text="+ 10(cm)")
        p1_perB3.config(width=10)
        p1_perB3.grid(row=7, column=1)
        p1_perB3.grid_configure(padx=(10, 0))

        p1_perB4 = tk.Button(self, text="- 10(cm)")
        p1_perB4.config(width=10)
        p1_perB4.grid(row=7, column=2)
        p1_perB4.grid_configure(padx=(0, 15))

        #  ********************AUTOMATISCH & HANDMATIG + INSTELLINGEN*******************
        p1_perB5 = tk.Button(self, text="Automatisch")
        p1_perB5.config(width=12)
        p1_perB5.grid(row=6, column=3)
        p1_perB5.grid_configure(padx=(15, 0))

        p1_perB6 = tk.Button(self, text="Handmatig")
        p1_perB6.config(width=12)
        p1_perB6.grid(row=6, column=4)

        p1_perB7 = tk.Button(self, text="Instellingen")
        p1_perB7.config(width=26)
        p1_perB7.grid(row=7, column=3, columnspan=2)
        p1_perB7.grid_configure(padx=(15, 0))

        #  ****************************************************ZONNESCHERM2**************************************************************
        p2_per_L1 = tk.Label(self, text="Zonnescherm 2")
        p2_per_L1.grid(row=0, columnspan=2, column=5, sticky="W")
        p2_per_L1.grid_configure(padx=(40, 0), pady=(20, 0))

        p2_per_L2 = tk.Label(self, text="Locatie:  " + "ZP11/D150")
        p2_per_L2.grid(row=1, columnspan=2, column=5, sticky="W")
        p2_per_L2.grid_configure(padx=(40, 0))

        #  ********************GEMIDDELDE TEMP + LICHT*******************
        p2_per_L3 = tk.Label(self, text="Gemiddelde temperatuur")
        p2_per_L3.grid(row=2, columnspan=2, column=5, sticky="WE")
        p2_per_L3.grid_configure(padx=(15, 15))

        p2_per_L4 = tk.Label(self, text="Gemiddelde lichtintensiteit")
        p2_per_L4.grid(row=2, column=7, columnspan=2, sticky="WE")
        p2_per_L4.grid_configure(padx=(15, 0))

        #  ********************STATUS(VALUE) & AFSTAND(VALUE)*******************
        p2_per_L5 = tk.Label(self, text="Status:")
        p2_per_L5.grid(row=4, column=5, sticky="W")
        p2_per_L5.grid_configure(padx=(15, 0))
        p2_per_L6 = tk.Label(self, text="test")
        p2_per_L6.grid(row=4, column=6, sticky="E")
        p2_per_L6.grid_configure(padx=(0, 15))

        p2_per_L7 = tk.Label(self, text="Afstand:")
        p2_per_L7.grid(row=5, column=5, sticky="W")
        p2_per_L7.grid_configure(padx=(15, 0))
        p2_per_L8 = tk.Label(self, text="1.60(CM)")
        p2_per_L8.grid(row=5, column=6, sticky="E")
        p2_per_L8.grid_configure(padx=(0, 15))

        #  ********************TEMP(VALUE) & LICHT(VALUE)*******************
        p2_per_L9 = tk.Label(self, text="Temperatuur:")
        p2_per_L9.grid(row=4, column=7, sticky="W")
        p2_per_L9.grid_configure(padx=(15, 0))
        p2_per_L10 = tk.Label(self, text="22.3")
        p2_per_L10.grid(row=4, column=8, sticky="E")
        p2_per_L10.grid_configure(padx=(0, 15))

        p2_per_L11 = tk.Label(self, text="Afstand:")
        p2_per_L11.grid(row=5, column=7, sticky="W")
        p2_per_L11.grid_configure(padx=(15, 0))
        p2_per_L12 = tk.Label(self, text="0.323")
        p2_per_L12.grid(row=5, column=8, sticky="E")
        p2_per_L12.grid_configure(padx=(0, 15))

        #  ********************tk.ButtonS*******************
        #  ********************UITROL & INROL tk.Button*******************
        p2_per_B1 = tk.Button(self, text="Uitrollen")
        p2_per_B1.config(width=10)
        p2_per_B1.grid(row=6, column=5)
        p2_per_B1.grid_configure(padx=(10, 0))

        p2_per_B2 = tk.Button(self, text="Inrollen")
        p2_per_B2.config(width=10)
        p2_per_B2.grid(row=6, column=6)
        p2_per_B2.grid_configure(padx=(0, 15))

        #  ********************+10(CM) & -10(CM)*******************
        p2_per_B3 = tk.Button(self, text="+ 10(cm)")
        p2_per_B3.config(width=10)
        p2_per_B3.grid(row=7, column=5)
        p2_per_B3.grid_configure(padx=(10, 0))

        p2_per_B4 = tk.Button(self, text="- 10(cm)")
        p2_per_B4.config(width=10)
        p2_per_B4.grid(row=7, column=6)
        p2_per_B4.grid_configure(padx=(0, 15))

        #  ********************AUTOMATISCH & HANDMATIG + INSTELLINGEN*******************
        p2_per_B5 = tk.Button(self, text="Automatisch")
        p2_per_B5.config(width=12)
        p2_per_B5.grid(row=6, column=7)
        p2_per_B5.grid_configure(padx=(15, 0))

        p2_per_B6 = tk.Button(self, text="Handmatig")
        p2_per_B6.config(width=12)
        p2_per_B6.grid(row=6, column=8)
        p2_per_B6.grid_configure(padx=(0, 15))

        p2_per_B7 = tk.Button(self, text="Instellingen")
        p2_per_B7.config(width=26)
        p2_per_B7.grid(row=7, column=7, columnspan=2)
        p2_per_B7.grid_configure(padx=(15, 15))

        #  ****************************************************ZONNESCHERM3**************************************************************
        p1_perL1 = tk.Label(self, text="Zonnescherm 3")
        p1_perL1.grid(row=8, columnspan=2, column=1, sticky="W")
        p1_perL1.grid_configure(padx=(40, 0), pady=(20, 0))

        p1_perL2 = tk.Label(self, text="Locatie:  " + "ZP11/D150")
        p1_perL2.grid(row=9, columnspan=2, column=1, sticky="W")
        p1_perL2.grid_configure(padx=(40, 0))

        #  ********************GEMIDDELDE TEMP + LICHT*******************
        p1_perL3 = tk.Label(self, text="Gemiddelde temperatuur")
        p1_perL3.grid(row=10, columnspan=2, column=1, sticky="WE")
        p1_perL3.grid_configure(padx=(15, 15))

        p1_perL4 = tk.Label(self, text="Gemiddelde lichtintensiteit")
        p1_perL4.grid(row=10, column=3, columnspan=2, sticky="WE")
        p1_perL4.grid_configure(padx=(15, 0))

        #  ********************STATUS(VALUE) & AFSTAND(VALUE)*******************
        p1_perL5 = tk.Label(self, text="Status:")
        p1_perL5.grid(row=12, column=1, sticky="W")
        p1_perL5.grid_configure(padx=(15, 0))
        p1_perL6 = tk.Label(self, text="test")
        p1_perL6.grid(row=12, column=2, sticky="E")
        p1_perL6.grid_configure(padx=(0, 15))

        p1_perL7 = tk.Label(self, text="Afstand:")
        p1_perL7.grid(row=13, column=1, sticky="W")
        p1_perL7.grid_configure(padx=(15, 0))
        p1_perL8 = tk.Label(self, text="1.60(CM)")
        p1_perL8.grid(row=13, column=2, sticky="E")
        p1_perL8.grid_configure(padx=(0, 15))

        #  ********************TEMP(VALUE) & LICHT(VALUE)*******************
        p1_perL9 = tk.Label(self, text="Temperatuur:")
        p1_perL9.grid(row=12, column=3, sticky="W")
        p1_perL9.grid_configure(padx=(15, 0))
        p1_perL10 = tk.Label(self, text="22.3")
        p1_perL10.grid(row=12, column=4, sticky="E")

        p1_perL11 = tk.Label(self, text="Afstand:")
        p1_perL11.grid(row=13, column=3, sticky="W")
        p1_perL11.grid_configure(padx=(15, 0))
        p1_perL12 = tk.Label(self, text="0.323")
        p1_perL12.grid(row=13, column=4, sticky="E")

        #  ********************tk.ButtonS*******************
        #  ********************UITROL & INROL tk.Button*******************
        p1_perB1 = tk.Button(self, text="Uitrollen")
        p1_perB1.config(width=10)
        p1_perB1.grid(row=14, column=1)
        p1_perB1.grid_configure(padx=(10, 0))

        p1_perB2 = tk.Button(self, text="Inrollen")
        p1_perB2.config(width=10)
        p1_perB2.grid(row=14, column=2)
        p1_perB2.grid_configure(padx=(0, 15))

        #  ********************+10(CM) & -10(CM)*******************
        p1_perB3 = tk.Button(self, text="+ 10(cm)")
        p1_perB3.config(width=10)
        p1_perB3.grid(row=15, column=1)
        p1_perB3.grid_configure(padx=(10, 0))

        p1_perB4 = tk.Button(self, text="- 10(cm)")
        p1_perB4.config(width=10)
        p1_perB4.grid(row=15, column=2)
        p1_perB4.grid_configure(padx=(0, 15))

        #  ********************AUTOMATISCH & HANDMATIG + INSTELLINGEN*******************
        p1_perB5 = tk.Button(self, text="Automatisch")
        p1_perB5.config(width=12)
        p1_perB5.grid(row=14, column=3)
        p1_perB5.grid_configure(padx=(15, 0))

        p1_perB6 = tk.Button(self, text="Handmatig")
        p1_perB6.config(width=12)
        p1_perB6.grid(row=14, column=4)

        p1_perB7 = tk.Button(self, text="Instellingen")
        p1_perB7.config(width=26)
        p1_perB7.grid(row=15, column=3, columnspan=2)
        p1_perB7.grid_configure(padx=(15, 0))

        #  ****************************************************ZONNESCHERM4**************************************************************
        p2_per_L1 = tk.Label(self, text="Zonnescherm 4")
        p2_per_L1.grid(row=8, columnspan=2, column=5, sticky="W")
        p2_per_L1.grid_configure(padx=(40, 0), pady=(20,))

        p2_per_L2 = tk.Label(self, text="Locatie:  " + "ZP11/D150")
        p2_per_L2.grid(row=9, columnspan=2, column=5, sticky="W")
        p2_per_L2.grid_configure(padx=(40, 0))

        #  ********************GEMIDDELDE TEMP + LICHT*******************
        p2_per_L3 = tk.Label(self, text="Gemiddelde temperatuur")
        p2_per_L3.grid(row=10, columnspan=2, column=5, sticky="WE")
        p2_per_L3.grid_configure(padx=(15, 15))

        p2_per_L4 = tk.Label(self, text="Gemiddelde lichtintensiteit")
        p2_per_L4.grid(row=10, column=7, columnspan=2, sticky="WE")
        p2_per_L4.grid_configure(padx=(15, 0))

        #  ********************STATUS(VALUE) & AFSTAND(VALUE)*******************
        p2_per_L5 = tk.Label(self, text="Status:")
        p2_per_L5.grid(row=12, column=5, sticky="W")
        p2_per_L5.grid_configure(padx=(15, 0))
        p2_per_L6 = tk.Label(self, text="test")
        p2_per_L6.grid(row=12, column=6, sticky="E")
        p2_per_L6.grid_configure(padx=(0, 15))

        p2_per_L7 = tk.Label(self, text="Afstand:")
        p2_per_L7.grid(row=13, column=5, sticky="W")
        p2_per_L7.grid_configure(padx=(15, 0))
        p2_per_L8 = tk.Label(self, text="1.60 (CM)")
        p2_per_L8.grid(row=13, column=6, sticky="E")
        p2_per_L8.grid_configure(padx=(0, 15))

        #  ********************TEMP(VALUE) & LICHT(VALUE)*******************
        p2_per_L9 = tk.Label(self, text="Temperatuur:")
        p2_per_L9.grid(row=12, column=7, sticky="W")
        p2_per_L9.grid_configure(padx=(15, 0))
        p2_per_L10 = tk.Label(self, text="22.3")
        p2_per_L10.grid(row=12, column=8, sticky="E")
        p2_per_L10.grid_configure(padx=(0, 15))

        p2_per_L11 = tk.Label(self, text="Afstand:")
        p2_per_L11.grid(row=13, column=7, sticky="W")
        p2_per_L11.grid_configure(padx=(15, 0))
        p2_per_L12 = tk.Label(self, text="0.323")
        p2_per_L12.grid(row=13, column=8, sticky="E")
        p2_per_L12.grid_configure(padx=(0, 15))

        #  ********************tk.ButtonS*******************
        #  ********************UITROL & INROL tk.Button*******************
        p2_per_B1 = tk.Button(self, text="Uitrollen")
        p2_per_B1.config(width=10)
        p2_per_B1.grid(row=14, column=5)
        p2_per_B1.grid_configure(padx=(10, 0))

        p2_per_B2 = tk.Button(self, text="Inrollen")
        p2_per_B2.config(width=10)
        p2_per_B2.grid(row=14, column=6)
        p2_per_B2.grid_configure(padx=(0, 15))

        #  ********************+10(CM) & -10(CM)*******************
        p2_per_B3 = tk.Button(self, text="+ 10(cm)")
        p2_per_B3.config(width=10)
        p2_per_B3.grid(row=15, column=5)
        p2_per_B3.grid_configure(padx=(10, 0))

        p2_per_B4 = tk.Button(self, text="- 10(cm)")
        p2_per_B4.config(width=10)
        p2_per_B4.grid(row=15, column=6)
        p2_per_B4.grid_configure(padx=(0, 15))

        #  ********************AUTOMATISCH & HANDMATIG + INSTELLINGEN*******************
        p2_per_B5 = tk.Button(self, text="Automatisch")
        p2_per_B5.config(width=12)
        p2_per_B5.grid(row=14, column=7)
        p2_per_B5.grid_configure(padx=(15, 0))

        p2_per_B6 = tk.Button(self, text="Handmatig")
        p2_per_B6.config(width=12)
        p2_per_B6.grid(row=14, column=8)
        p2_per_B6.grid_configure(padx=(0, 15))

        p2_per_B7 = tk.Button(self, text="Instellingen")
        p2_per_B7.config(width=26)
        p2_per_B7.grid(row=15, column=7, columnspan=2)
        p2_per_B7.grid_configure(padx=(15, 15))
        #  ********************BUTTON WINDOWS*******************
        B = tk.Button(self, text="Per Paneel",
                      command=lambda: controller.show_frame("PerPaneel"))
        B.config(width=10)
        B.grid(row=3, pady=2)

        B1 = tk.Button(self, text="Alle Panelen",
                       command=lambda: controller.show_frame("AllePanelen"))
        B1.config(width=10)
        B1.grid(row=4, pady=2)

        B3 = tk.Button(self, text="Instellingen",
                       command=lambda: controller.show_frame("Instellingen"))
        B3.config(width=10)
        B3.grid(row=5, pady=2)
        self.after(2000, _thread.start_new_thread, self.GetValues, ())


    def GetValues(self, Test=None):

        while (1):
            if Test == None:
                ser.write('GET_ALL'.encode() + bytes([13]))
                response = ser.read(ser.inWaiting()).decode('ascii')
                response = re.sub('Wat kan ik voor u doen', '', response)
                response = re.sub('GET_ALL', '', response)
                response = response[2:-2]
                self.TempValue.set(str(response[8:14]))
                response = response[14:]
                self.LightValue.set(str(response[13:17]))
                response = response[17:]
                self.DistanceValue.set(str(response[14:23]))
                response = response[23:]
                print(response)

            if Test == "Uirollen":
                print("Test")
            time.sleep(1)




class AllePanelen(tk.Frame):

    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.controller = controller

        f1 = tk.Frame(self)
        f1.grid(row=0, column=1)
        f2 = tk.Frame(self)
        f2.grid(row=0, column=0)

        alle_tkvarT1 = tk.StringVar(f1)
        alle_tkvarT2 = tk.StringVar(f1)
        alle_tkvarL1 = tk.StringVar(f1)
        alle_tkvarL2 = tk.StringVar(f1)
        #  ********************LABELS*******************
        #  ********************NAAM + INFO*******************
        alle_L1 = tk.Label(f1, text="Alle panelen")
        alle_L1.grid(row=0, column=1, columnspan=2, sticky="W")
        alle_L1.grid_configure(padx=(40, 0))

        alle_L2 = tk.Label(f1, text="De bediening geldt voor alle zonnepanelen")
        alle_L2.grid(row=1, column=1, columnspan=3, sticky="W")
        alle_L2.grid_configure(padx=(15, 0))

        #  ********************GEMIDDELDE TEMP + LICHT*******************
        alle_L3 = tk.Label(f1, text="Gemiddelde temperatuur")
        alle_L3.grid(row=2, column=1, columnspan=2, sticky="W")
        alle_L3.grid_configure(padx=(15, 15))

        alle_L4 = tk.Label(f1, text="Gemiddelde lichtintensiteit")
        alle_L4.grid(row=2, column=5, columnspan=2, sticky="W")
        alle_L4.grid_configure(padx=(15, 0))

        #  ********************PANELEN + TIJD (TEMP)*******************
        alle_L5 = tk.Label(f1, text="Panelen")
        alle_L5.grid(row=4, column=1, sticky="W")
        alle_L5.grid_configure(padx=(15, 0))

        alle_L6 = tk.Label(f1, text="Tijd")
        alle_L6.grid(row=5, column=1, sticky="W")
        alle_L6.grid_configure(padx=(15, 0))

        alle_L7 = tk.Label(f1, text="Panelen")
        alle_L7.grid(row=4, column=5, sticky="W")
        alle_L7.grid_configure(padx=(15, 0))

        alle_L8 = tk.Label(f1, text="Tijd")
        alle_L8.grid(row=5, column=5, sticky="W")
        alle_L8.grid_configure(padx=(15, 0))

        #  ********************DROP DOWN MENU'S*******************
        choices_panelen = {'Zonnescherm 1', 'Zonnescherm 2', 'Zonnescherm 3', 'Alle zonneschermen'}
        alle_tkvarT1.set('Alle zonneschermen')
        alle_tkvarT2.set('Alle zonneschermen')
        alle_DP1 = tk.OptionMenu(f1, alle_tkvarT1, *choices_panelen)
        alle_DP1.config(width=45)
        alle_DP1.grid(row=4, column=2, columnspan=3, sticky="E")

        choices_tijd = {'Tijd 0', 'Tijd 1', 'Tijd 2', 'Tijd 3'}
        alle_tkvarL1.set('Alle tijden')
        alle_tkvarL2.set('Alle tijden')
        alle_DT1 = tk.OptionMenu(f1, alle_tkvarL1, *choices_tijd)
        alle_DT1.config(width=45)
        alle_DT1.grid(row=5, column=2, columnspan=3, sticky="E")

        alle_DP2 = tk.OptionMenu(f1, alle_tkvarT2, *choices_panelen)
        alle_DP2.config(width=45)
        alle_DP2.grid(row=4, column=6, columnspan=3, sticky="E")

        alle_DT2 = tk.OptionMenu(f1, alle_tkvarL2, *choices_tijd)
        alle_DT2.config(width=45)
        alle_DT2.grid(row=5, column=6, columnspan=3, sticky="E")

        #  ********************BUTTONS*******************
        #  ********************UITROL & INROL tk.Button*******************
        alle_B1 = tk.Button(f1, text="Uitrollen")
        alle_B1.config(width=10)
        alle_B1.grid(row=6, column=1)
        alle_B1.grid_configure(padx=(10, 0))

        alle_B2 = tk.Button(f1, text="Inrollen")
        alle_B2.config(width=10)
        alle_B2.grid(row=6, column=2)
        alle_B2.grid_configure(padx=(0, 15))

        #  ********************+10(CM) & -10(CM)*******************
        alle_B3 = tk.Button(f1, text="+ 10(cm)")
        alle_B3.config(width=10)
        alle_B3.grid(row=7, column=1)
        alle_B3.grid_configure(padx=(10, 0))

        alle_B4 = tk.Button(f1, text="- 10(cm)")
        alle_B4.config(width=10)
        alle_B4.grid(row=7, column=2)
        alle_B4.grid_configure(padx=(0, 15))

        #  ********************AUTOMATISCH & HANDMATIG + INSTELLINGEN*******************
        alle_B5 = tk.Button(f1, text="Automatisch")
        alle_B5.config(width=12)
        alle_B5.grid(row=6, column=3)
        alle_B5.grid_configure(padx=(15, 0))

        alle_B6 = tk.Button(f1, text="Handmatig")
        alle_B6.config(width=12)
        alle_B6.grid(row=6, column=4)

        alle_B7 = tk.Button(f1, text="Instellingen")
        alle_B7.config(width=26)
        alle_B7.grid(row=7, column=3, columnspan=2)
        alle_B7.grid_configure(padx=(15, 0))

        B1 = tk.Button(f2, text="Per Paneel",
                       command=lambda: controller.show_frame("PerPaneel"))
        B1.config(width=10)
        B1.grid(pady=2)

        B = tk.Button(f2, text="Alle Panelen",
                      command=lambda: controller.show_frame("AllePanelen"))
        B.config(width=10)
        B.grid(pady=2)

        B3 = tk.Button(f2, text="Instellingen",
                       command=lambda: controller.show_frame("Instellingen"))
        B3.config(width=10)
        B3.grid(pady=2)


class Instellingen(tk.Frame):

    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.controller = controller

        "self.after(2000, _thread.start_new_thread, self.GetTemp, ())"

        self.TempValue = tk.StringVar()
        f1 = tk.Frame(self)
        f1.grid(row=0, column=1)
        f2 = tk.Frame(self)
        f2.grid(row=0, column=0)
        var1 = tk.StringVar()
        var = tk.StringVar()

        inst_L1 = tk.Label(f1, text="Instellingen")
        inst_L1.grid(row=0, column=1, columnspan=2, sticky="W")
        inst_L1.grid_configure(padx=(15, 0), pady=(15, 5))

        inst_M1 = tk.Message(f1, textvariable=var)
        inst_M1.grid(row=1, column=1, columnspan=2, sticky="W")
        inst_M1.grid_configure(padx=(15, 0))
        inst_M1.config(width=300)
        var.set("Dit is nog wat extra tekst wat je zou verwachten bij een instellingen panel?")

        inst_L2 = tk.Label(f1, text="Algemene Instellingen")
        inst_L2.grid(row=2, column=1, columnspan=2, sticky="W")
        inst_L2.grid_configure(padx=(15, 0), pady=(25, 5))

        inst_M2 = tk.Message(f1, textvariable=self.TempValue)
        inst_M2.grid(row=3, column=1, columnspan=2, sticky="W")
        inst_M2.grid_configure(padx=(15, 0))
        inst_M2.config(width=300)
        var1.set("Dit is nog wat extra tekst wat je zou verwachten bij een algemene instellingen panel!!!!!!")

        inst_L3 = tk.Label(f1, text="Per Zonnescherm")
        inst_L3.grid(row=4, column=1, sticky="W")
        inst_L3.grid_configure(padx=(15, 0), pady=(25, 10))
        #  ********************NAMEN ZONNESCHERM*******************

        inst_L4 = tk.Label(f1, text="Naam", relief="ridge")
        inst_L4.grid(row=5, column=1, sticky="W")
        inst_L4.config(width=30)
        inst_L4.grid_configure(padx=(20, 0))

        inst_L5 = tk.Label(f1, text="Zonnescherm 1", relief="sunken")
        inst_L5.grid(row=6, column=1, sticky="W")
        inst_L5.config(width=30)
        inst_L5.grid_configure(padx=(20, 0))

        inst_L6 = tk.Label(f1, text="Zonnescherm 2", relief="ridge")
        inst_L6.grid(row=7, column=1, sticky="W")
        inst_L6.config(width=30)
        inst_L6.grid_configure(padx=(20, 0))

        inst_L7 = tk.Label(f1, text="Zonnescherm 3", relief="sunken")
        inst_L7.grid(row=8, column=1, sticky="W")
        inst_L7.config(width=30)
        inst_L7.grid_configure(padx=(20, 0))

        inst_L8 = tk.Label(f1, text="Zonnescherm 4", relief="ridge")
        inst_L8.grid(row=9, column=1, sticky="W")
        inst_L8.config(width=30)
        inst_L8.grid_configure(padx=(20, 0))

        #  ********************LOCATIE ZONNESCHERM*******************

        inst_L9 = tk.Label(f1, text="Locatie", relief="sunken")
        inst_L9.grid(row=5, column=2, sticky="W")
        inst_L9.config(width=30)

        inst_L10 = tk.Label(f1, text="ZP11/D150", relief="ridge")
        inst_L10.grid(row=6, column=2, sticky="W")
        inst_L10.config(width=30)

        inst_L11 = tk.Label(f1, text="ZP11/D151", relief="ridge")
        inst_L11.grid(row=7, column=2, sticky="W")
        inst_L11.config(width=30)

        inst_L12 = tk.Label(f1, text="ZP11/D152", relief="ridge")
        inst_L12.grid(row=8, column=2, sticky="W")
        inst_L12.config(width=30)

        inst_L13 = tk.Label(f1, text="ZP11/D153", relief="ridge")
        inst_L13.grid(row=9, column=2, sticky="W")
        inst_L13.config(width=30)

        #  ********************ACTIE ZONNESCHERM*******************

        inst_L14 = tk.Label(f1, text="Actie", relief="ridge")
        inst_L14.grid(row=5, column=3, columnspan=2, sticky="W")
        inst_L14.config(width=42)

        inst_B1 = tk.Button(f1, text="Wijzigen", command=lambda: controller.show_frame1("Wijzigen"))
        inst_B1.grid(row=6, column=3, sticky="W")
        inst_B1.config(width=20)

        inst_B2 = tk.Button(f1, text="Wijzigen")
        inst_B2.grid(row=7, column=3, sticky="W")
        inst_B2.config(width=20)

        inst_B3 = tk.Button(f1, text="Wijzigen")
        inst_B3.grid(row=8, column=3, sticky="W")
        inst_B3.config(width=20)

        inst_B4 = tk.Button(f1, text="Wijzigen")
        inst_B4.grid(row=9, column=3, sticky="W")
        inst_B4.config(width=20)

        inst_B5 = tk.Button(f1, text="Verwijderen")
        inst_B5.grid(row=6, column=4, sticky="W")
        inst_B5.config(width=20)

        inst_B6 = tk.Button(f1, text="Verwijderen")
        inst_B6.grid(row=7, column=4, sticky="W")
        inst_B6.config(width=20)

        inst_B7 = tk.Button(f1, text="Verwijderen")
        inst_B7.grid(row=8, column=4, sticky="W")
        inst_B7.config(width=20)

        inst_B8 = tk.Button(f1, text="Verwijderen")
        inst_B8.grid(row=9, column=4, sticky="W")
        inst_B8.config(width=20)

        B = tk.Button(self, text="Per Paneel",
                      command=lambda: controller.show_frame("PerPaneel"))
        B.config(width=10)
        B.grid(row=3, pady=2)

        B1 = tk.Button(self, text="Alle Panelen",
                       command=lambda: controller.show_frame("AllePanelen"))
        B1.config(width=10)
        B1.grid(row=4, pady=2)

        B3 = tk.Button(self, text="Instellingen",
                       command=lambda: controller.show_frame("Instellingen"))
        B3.config(width=10)
        B3.grid(row=5, pady=2)


class Wijzigen(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.controller = controller

        f1 = tk.Frame(self)
        f1.grid(row=0, column=1)
        f2 = tk.Frame(self)
        f2.grid(row=0, column=0)
        # *************************************ZONNESCHERM_1**************************************************

        wijz_L1 = tk.Label(f1, text="Naam")
        wijz_L1.grid(row=1, column=1, columnspan=2, sticky="E")
        wijz_L1.grid_configure(padx=(15, 0))
        wijz_E1 = tk.Entry(f1)
        wijz_E1.insert(0, "a default value")
        wijz_E1.grid(row=1, column=3, sticky="E")

        wijz_L2 = tk.Label(f1, text="Locatie")
        wijz_L2.grid(row=2, column=1, columnspan=2, sticky="E")
        wijz_L2.grid_configure(padx=(15, 0))
        wijz_E2 = tk.Entry(f1)
        wijz_E2.grid(row=2, column=3, sticky="W")

        wijz_L3 = tk.Label(f1, text="Maximale uitrol")
        wijz_L3.grid(row=3, column=1, columnspan=2, sticky="E")
        wijz_L3.grid_configure(padx=(15, 0))
        wijz_E3 = tk.Entry(f1)
        wijz_E3.grid(row=3, column=3, sticky="W")

        wijz_L4 = tk.Label(f1, text="Maximale inrol")
        wijz_L4.grid(row=4, column=1, columnspan=2, sticky="E")
        wijz_L4.grid_configure(padx=(15, 0))
        wijz_E4 = tk.Entry(f1)
        wijz_E4.grid(row=4, column=3, sticky="W")

        wijz_L5 = tk.Label(f1, text="Grenswaarde lichtintensiteit")
        wijz_L5.grid(row=5, column=1, columnspan=2, sticky="W")
        wijz_L5.grid_configure(padx=(15, 0))
        wijz_E5 = tk.Entry(f1)
        wijz_E5.grid(row=5, column=3, sticky="W")

        wijz_L6 = tk.Label(f1, text="Grenswaarde Temperatuur")
        wijz_L6.grid(row=6, column=1, columnspan=2, sticky="W")
        wijz_L6.grid_configure(padx=(15, 0))
        wijz_E6 = tk.Entry(f1)
        wijz_E6.grid(row=6, column=3, sticky="W")

        I1_wijz_L1 = tk.Label(f1, text="Naam")
        I1_wijz_L1.grid(row=1, column=4, columnspan=2, sticky="E")
        I1_wijz_L1.grid_configure(padx=(15, 0))
        I2_wijz_L1 = tk.Label(f1, text="Franklin")
        I2_wijz_L1.grid(row=1, column=6, columnspan=2, sticky="W")
        I2_wijz_L1.grid_configure(padx=(15, 0))

        I1_wijz_L2 = tk.Label(f1, text="Locatie")
        I1_wijz_L2.grid(row=2, column=4, columnspan=2, sticky="E")
        I1_wijz_L2.grid_configure(padx=(15, 0))
        I2_wijz_L2 = tk.Label(f1, text="Zernikeplein")
        I2_wijz_L2.grid(row=2, column=6, columnspan=2, sticky="W")
        I2_wijz_L2.grid_configure(padx=(15, 0))

        I1_wijz_L3 = tk.Label(f1, text="Maximale uitrol")
        I1_wijz_L3.grid(row=3, column=4, columnspan=2, sticky="E")
        I1_wijz_L3.grid_configure(padx=(15, 0))
        I2_wijz_L3 = tk.Label(f1, text="30(CM)")
        I2_wijz_L3.grid(row=3, column=6, columnspan=2, sticky="W")
        I2_wijz_L3.grid_configure(padx=(15, 0))

        I1_wijz_L4 = tk.Label(f1, text="Maximale inrol")
        I1_wijz_L4.grid(row=4, column=4, columnspan=2, sticky="E")
        I1_wijz_L4.grid_configure(padx=(15, 0))
        I2_wijz_L4 = tk.Label(f1, text="6(CM)")
        I2_wijz_L4.grid(row=4, column=6, columnspan=2, sticky="W")
        I2_wijz_L4.grid_configure(padx=(15, 0))

        I1_wijz_L5 = tk.Label(f1, text="Grenswaarde lichtinsiteit")
        I1_wijz_L5.grid(row=5, column=4, columnspan=2, sticky="E")
        I1_wijz_L5.grid_configure(padx=(15, 0))
        I2_wijz_L5 = tk.Label(f1, text="230")
        I2_wijz_L5.grid(row=5, column=6, columnspan=2, sticky="W")
        I2_wijz_L5.grid_configure(padx=(15, 0))

        I1_wijz_L6 = tk.Label(f1, text="Grenswaarde temperatuur")
        I1_wijz_L6.grid(row=6, column=4, columnspan=2, sticky="E")
        I1_wijz_L6.grid_configure(padx=(15, 0))
        I2_wijz_L6 = tk.Label(f1, text="22.56")
        I2_wijz_L6.grid(row=6, column=6, columnspan=2, sticky="W")
        I2_wijz_L6.grid_configure(padx=(15, 0))

        # ********************************************BUTTONS*********************************************
        wijz_B1 = tk.Button(f1, text="Opslaan")
        wijz_B1.grid(row=33, column=1, sticky="W")
        wijz_B1.grid_configure(padx=(15, 0), pady=(10, 0))

        wijz_B2 = tk.Button(f1, text="Anuleren", command=quit)
        wijz_B2.grid(row=33, column=3, sticky="W")
        wijz_B2.grid_configure(pady=(10, 0))

        B = tk.Button(self, text="Per Paneel",
                      command=lambda: controller.show_frame("PerPaneel"))
        B.config(width=10)
        B.grid(row=3, pady=2)

        B1 = tk.Button(self, text="Alle Panelen",
                       command=lambda: controller.show_frame("AllePanelen"))
        B1.config(width=10)
        B1.grid(row=4, pady=2)

        B3 = tk.Button(self, text="Instellingen",
                       command=lambda: controller.show_frame("Instellingen"))
        B3.config(width=10)
        B3.grid(row=5, pady=2)


if __name__ == "__main__":
    app = SampleApp()
    app.mainloop()
