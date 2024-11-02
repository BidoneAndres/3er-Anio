from antlr4.tree.Tree import ErrorNode, TerminalNode
from compiladoresListener import compiladoresListener
from compiladoresParser import compiladoresParser
from TablaSimbolos import TablaSimbolos
from Contexto import Contexto
from Id import ID


class Escucha(compiladoresListener) :


    TablaSimbolos = TablaSimbolos()    

    
    numTokens = 0
    numNode = 0

    # Vemos el comienzo del programa
    # -----------------------------------------------------------
    def enterPrograma(self, ctx:compiladoresParser.ProgramaContext):
        print("Comienza la Compilacion")

    # Exit a parse tree produced by compiladoresParser#programa.
    def exitPrograma(self, ctx:compiladoresParser.ProgramaContext):
        print("Fin de la compilacion")
        print("Se encontraron")
        print("\tNodos: "+str(self.numNode))
        print("\tTokens: "+str(self.numTokens))
    # -----------------------------------------------------------

    #Cuando usamos un bloque, estoy probando con while 
    # -----------------------------------------------------------
    def enterBloque(self, ctx: compiladoresParser.BloqueContext):
        print("---> Encontre un BLOQUE")
        #context = Contexto()
       # self.TablaSimbolos.addContexto(TablaSimbolos,context)
        
    def exitBloque(self, ctx: compiladoresParser.BloqueContext):
        
        print ("Salgo de un bloque")
        #print ("Cantidad de hijos: " + str(ctx.getChildCount()))
        #print("Tokens: " + str(ctx.getText()))

 #       print("Se encontro:")
  #      TablaSimbolos.contextos[-1].imprimirTabla()
   #     TablaSimbolos.delContexto(TablaSimbolos)

        return super().exitBloque(ctx)
    # -----------------------------------------------------------

    #Ecuchamos si viene un while entonces hacemos...
    # -----------------------------------------------------------       
    def enterIWhile(self, ctx:compiladoresParser.IwhileContext):
        print("Encontre WHILE")
        print ("--------------------------------------")
        #print("\tCantidad hijos: "+ctx.getChildCount)
        #print("\tTOQUENS: "+ctx.getText)

    def exitIWhile(self, ctx:compiladoresParser.IwhileContext):
        

        iwhile = ctx.getChild(0).getText()
        condicional = ctx.getChild(2).getText()


        print ("--------------------------------------")
        
        print ( "---> Funcion: " + iwhile )
        print ( "---> Condicional: " + condicional )

        print ("--------------------------------------")
        print("Fin de WHILE")

        
        #print("\tCantidad hijos: "+ctx.getChildCount)
        #print("\tTOQUENS: "+ctx.getText)
    # -----------------------------------------------------------

    


    #Aca declaramos cuando inicializamos las variables...
    # -----------------------------------------------------------

    def enterInit(self, ctx: compiladoresParser.InitContext):
        print ("---> Inicializamos una variable") 
        return super().enterInit(ctx)
    



    def exitInit(self, ctx: compiladoresParser.InitContext):
        
        tipoDato = ctx.getChild(0).getText()
        nombre = ctx.getChild(1).getText()

        comprobarGlobal = TablaSimbolos.buscarGlobal(TablaSimbolos, nombre)

        if comprobarGlobal == 1 :

            if TablaSimbolos.buscarLocal( TablaSimbolos, nombre) == 1:
                print ("Se agrego correctamente la variable")
                print ("--------------------------------------")
        
                print("--->Tipo de dato: " + tipoDato)
                print("--->Nombre de Variable: " + nombre ) 

                print ("--------------------------------------")
        
                TablaSimbolos.addIdentificador(TablaSimbolos, nombre, tipoDato)
            else: 
                print ("---> El id ya esta en uso...")
        else :
            print ("---> El id ya esta en uso...")

        return super().exitInit(ctx)
    # -----------------------------------------------------------
    

    #Esta parte la vamos a usar para las asignaciones.
    # -----------------------------------------------------------
    def enterAsignacion(self, ctx: compiladoresParser.AsignacionContext):
        
        print("---> Se encontro una asignacion...")
        
        return super().enterAsignacion(ctx)
    
    def exitAsignacion(self, ctx: compiladoresParser.AsignacionContext):

        nombre = ctx.getChild(0).getText()
        valor = ctx.getChild(2).getText()
        
        buscarLocal = TablaSimbolos.buscarLocal(TablaSimbolos, nombre)

        if buscarLocal != 1 : 
            print("La variable ' " + nombre + " ' se le asigno el valor ' " + valor + " ' ")
            buscarLocal.inicializado = 1
            

        else:
            print("ERROR, la variable no a sido inicializada...")

        return super().exitAsignacion(ctx)
        

    # -----------------------------------------------------------
    # Exit a parse tree produced by compiladoresParser#programa.


    def exitPrograma(self, ctx:compiladoresParser.ProgramaContext):
         print("Nombre Variable: "+ ctx.getChild(1).getText())  
         
    def visitTerminal(self, node: TerminalNode):
        print("----> Token: " + node.getText())
        self.numTokens =+ 1
        
    def visitErrorNode(self, node: ErrorNode):
        print("----> ERROR ")
        
    def enterEveryRule(self, ctx):
        self.numNode += 1

    #Aca se va a declarar las fuciones...
     # -----------------------------------------------------------
   
    def enterFunc(self, ctx: compiladoresParser.FuncContext):
        print("---> Se ingreso una funcion... ")
        
        return super().enterFunc(ctx)
    
    def exitFunc(self, ctx: compiladoresParser.FuncContext):
        
        retorno = ctx.getChild(0).getText()
        nombrefuncion = ctx.getChild(1).getText()

        buscarGlobal = TablaSimbolos.buscarGlobal(TablaSimbolos, nombrefuncion)

        comprobar = False
        listaParametros = []

        if buscarGlobal == 1:
            print ( "ERROR, la funcion no tiene declarado un prototipo" )
            return None;
        parametros = ctx.var_func()

        if parametros and parametros.getChildCount() > 0:
                
            comprobar = True

            i = 0
            while i < parametros.getChildCount() :
            
                tipo = parametros.getChild(i).getText()
                nombre = parametros. getChild(i+1).getText()
                listaParametros.append(f"{tipo} {nombre}")
                i+=3

            print ("---> La funcion ' " + nombrefuncion + " ' fue ingresada correctamente")
            print ("--------------------------------------")
            print ("Nombre: " + nombrefuncion)
            print ("Tipo de Retorno: " + retorno)
            
        if comprobar :
            print("Parametros: ")
            print(listaParametros)
        else :
            print("La funcion no necesita parametros")    
        print ("--------------------------------------")       

        
        

    #Aca declaramos el prototipo 
    # -----------------------------------------------------------
    def enterProto(self, ctx: compiladoresParser.ProtoContext):
        print ("---> Encontre un prototipo")
        return super().enterProto(ctx)
    
    def exitProto(self, ctx: compiladoresParser.ProtoContext):
        
        retorno = ctx.getChild(0).getText()
        nombrePrototipo = ctx.getChild(1).getText()


        buscarGlobal = TablaSimbolos.buscarGlobal(TablaSimbolos, nombrePrototipo)

        comprobar = False
        listaParametros = []

        if buscarGlobal == 1 :

            parametros = ctx.var_func()

            if parametros and parametros.getChildCount() > 0:
                
                comprobar = True

                i = 0

                while i < parametros.getChildCount() :
            
                    tipo = parametros.getChild(i).getText()
                    nombre = parametros. getChild(i+1).getText()
                    listaParametros.append(f"{tipo} {nombre}")

                    i+=3

            print ("---> La funcion ' " + nombrePrototipo + " ' fue ingresada correctamente")
            print ("--------------------------------------")
            print ("Nombre: " + nombrePrototipo)
            print ("Tipo de Retorno: " + retorno)
            
            if comprobar :
                print("Parametros: ")
                print(listaParametros)
            else :
                print("La funcion no necesita parametros")
            
            print ("--------------------------------------")       
            TablaSimbolos.addIdentificador(TablaSimbolos, nombrePrototipo, retorno )
        else :
            print("ERROR!!! La funcion ' " + nombrePrototipo + " ' ya existe")
            return None
        return super().exitProto(ctx)
    # -----------------------------------------------------------

    #Esta parte la vamos a usar para comprobar si los factores de las opal estan todos definidos
    #------------------------------------------------------------------
    def enterFactor(self, ctx: compiladoresParser.FactorContext):
        
        return super().enterFactor(ctx)

    def exitFactor(self, ctx: compiladoresParser.FactorContext):
        
        nombreVariable = ctx.ID() #Aca lo que puede pasar es que no tengamos un id como factor, entonces devuelve none en ese caso

        if nombreVariable != None : 
            busqueda = TablaSimbolos.buscarLocal(TablaSimbolos, nombreVariable.getText()) #Aca lo que vamos a hacer es buscarlo dentro de la tabla de simbolos...
            #comprobamos is esta inicializada la variable
            if busqueda == 1:
                print( "ERROR, variable no existente" )
                return None
                
            if busqueda.inicializado == 1: 
                    #Vamos a definir la variable como usada

                    busqueda.usado = 1
            else :
                print("ERROR, la variable no a sido inicializada")
 
            if busqueda == 1:
                busqueda = TablaSimbolos.buscarGlobal(TablaSimbolos ,nombreVariable)

                if busqueda == 1:
                    print( "ERROR, variable no existente" )
                    return None
                
                #comprobamos si fue inicializada, si no fue asi no se conoce el valor, por lo que no podemos hacer nada con ella
                if busqueda.inicializado == 1: 
                    #Vamos a definir la variable como usada
                    busqueda.usado = 1 
                else :
                    print("ERROR, la variable no a sido inicializada")
                    

        return super().exitFactor(ctx)
    #Aca vamos a definir la llamadas a funciones...
    #------------------------------------------------------------------
    def enterCallFunc(self, ctx: compiladoresParser.CallFuncContext):
        return super().enterCallFunc(ctx)
    

    def exitCallFunc(self, ctx: compiladoresParser.CallFuncContext):
        
        nombre = ctx.getChild(0).getText()

        comprobarGlobal = TablaSimbolos.buscarGlobal(TablaSimbolos, nombre)

        if comprobarGlobal == 1 :

            print("ERROR, la funcion no esta definida")
            return None
        
        
        
        return super().exitCallFunc(ctx)
    #------------------------------------------------------------------
