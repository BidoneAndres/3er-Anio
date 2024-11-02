from compiladoresVisitor import compiladoresVisitor
from compiladoresParser import compiladoresParser

#Esto recorre nodo por nodo basicamente
class Walker (compiladoresVisitor) :
    def visitPrograma(self, ctx:compiladoresParser.ProgramaContext):
        print("=-"*20)
        print("--Comienza a caminar")
        tmp = super().visitPrograma(ctx)
        print("Fin del Recorrido")
        return tmp
    
    def visitDeclaracion(self, ctx):
        print (ctx.getChild(0).getText()+" - "+ctx.getChild(1))
        return none
    
    def visitBloque(self, ctx:compiladoresParser.BloqueContext):
        print("Nuevo Programa")
        return super().visitInstrucciones(ctx.getChild(1))

    def visitTerminal(self, node):
        print(" ==> Token "+ node.getText())
        return super().visitTerminal(node)
