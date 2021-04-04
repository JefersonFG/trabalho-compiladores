# Valida a etapa3 rodando uma vez no arquivo original e uma segunda no arquivo gerado
# Comparando os arquivos gerados nas duas etapas
./etapa3 exemplo.ere20202 saida_1.ere20202
./etapa3 saida_1.ere20202 saida_2.ere20202
diff saida_1.ere20202 saida_2.ere20202
