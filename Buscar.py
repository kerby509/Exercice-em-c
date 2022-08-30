import csv
import math
import random
import statistics
import time
from abc import abstractmethod


class Solucao:
    def __init__(self, qualidade, ciclo, tamanho, i_movimento, j_movimento):
        self.qualidade = qualidade
        self.ciclo = ciclo
        self.tamanho = tamanho
        self.i_movimento = i_movimento
        self.j_movimento = j_movimento

    def __str__(self):
        return "Ciclo: "+str(self.ciclo)+"\nQualidade: "+str(self.qualidade)+"\nTamanho: "+str(self.tamanho)


class Vizinhanca:
    def __init__(self, nome, qtd_trocas):
        self.nome = nome
        self.qtd_trocas = qtd_trocas

    @abstractmethod
    def computar_qualidade(self, solucao: Solucao, distancias: tuple, i: int, j: int) -> int:
        pass

    @abstractmethod
    def gerar_novo_ciclo(self, solucao: Solucao, i: int, j: int) -> list:
        pass

    @abstractmethod
    def melhor_vizinho(self, solucao: Solucao, distancias: tuple, tabu: set) -> Solucao:
        pass

    @abstractmethod
    def primeiro_vizinho_melhor(self, solucao: Solucao, distancias: tuple, tabu: set) -> Solucao:
        pass


class Vizinhanca2opt(Vizinhanca):
    def __init__(self):
        super().__init__("2opt", 2)

    def computar_qualidade(self, solucao: Solucao, distancias: tuple, i: int, j: int) -> int:
        qualidade = solucao.qualidade
        elemento_pre_i, elemento_i, elemento_pos_i, elemento_pre_j, elemento_j, elemento_pos_j \
            = retornar_elementos(solucao.ciclo, i, j)
        # i sempre < j
        qualidade += - distancias[elemento_i][elemento_pre_i] - distancias[elemento_j][elemento_pos_j] \
            + distancias[elemento_i][elemento_pos_j] + distancias[elemento_j][elemento_pre_i]
        return qualidade

    def gerar_novo_ciclo(self, solucao: Solucao, i: int, j: int) -> list:
        return solucao.ciclo[:i] + list(reversed(solucao.ciclo[i:j + 1])) + solucao.ciclo[j + 1:]

    def melhor_vizinho(self, solucao: Solucao, distancias: tuple, tabu: set) -> Solucao:
        melhor_qualidade = math.inf
        imelhor = -1
        jmelhor = -1
        for i in range(solucao.tamanho-1):
            if i not in tabu:
                for j in range(i+1, solucao.tamanho-1):
                    if j not in tabu:
                        qualidade = self.computar_qualidade(solucao, distancias, i, j)
                        if qualidade < melhor_qualidade:
                            melhor_qualidade = qualidade
                            imelhor = i
                            jmelhor = j
        return Solucao(melhor_qualidade, self.gerar_novo_ciclo(solucao, imelhor, jmelhor), solucao.tamanho, imelhor, jmelhor)

    def primeiro_vizinho_melhor(self, solucao: Solucao, distancias: tuple, tabu: set) -> Solucao:
        melhor_qualidade = solucao.qualidade
        for i in range(solucao.tamanho-1):
            if i not in tabu:
                for j in range(i + 1, solucao.tamanho-1):
                    if j not in tabu:
                        qualidade = self.computar_qualidade(solucao, distancias, i, j)
                        if qualidade < melhor_qualidade:
                            return Solucao(qualidade, self.gerar_novo_ciclo(solucao, i, j), solucao.tamanho, i, j)
        return solucao


class VizinhancaShift(Vizinhanca):
    def __init__(self):
        super().__init__("sh", 1)

    def computar_qualidade(self, solucao: Solucao, distancias: tuple, i: int, j: int) -> int:
        qualidade = solucao.qualidade
        elemento_pre_i, elemento_i, elemento_pos_i, elemento_pre_j, elemento_j, elemento_pos_j \
            = retornar_elementos(solucao.ciclo, i, j)
        # Elemento i é posicionado na posição de j, i sempre != de j
        if i < j:  # Deslocamento para a esquerda (elemento i movimenta-se para a direita na solução)
            qualidade += - distancias[elemento_i][elemento_pre_i] - distancias[elemento_j][elemento_pos_j] \
                         + distancias[elemento_i][elemento_pos_j]
            if j - i == 1:
                qualidade += distancias[elemento_j][elemento_pre_i]
            else:
                qualidade += - distancias[elemento_i][elemento_pos_i] \
                             + distancias[elemento_pre_i][elemento_pos_i] + distancias[elemento_j][elemento_i]
        else:  # Deslocamento para a direita (elemento i movimenta-se para a esquerda na solução)
            qualidade += - distancias[elemento_i][elemento_pos_i] - distancias[elemento_j][elemento_pre_j] \
                         + distancias[elemento_i][elemento_pre_j]
            if i - j == 1:
                qualidade += distancias[elemento_j][elemento_pos_i]
            else:
                qualidade += - distancias[elemento_i][elemento_pre_i] \
                             + distancias[elemento_pre_i][elemento_pos_i] + distancias[elemento_j][elemento_i]
        return qualidade

    def gerar_novo_ciclo(self, solucao: Solucao, i: int, j: int) -> list:
        if i < j:
            ciclo = solucao.ciclo[:i] + solucao.ciclo[i + 1:j + 1] + [solucao.ciclo[i]] + solucao.ciclo[j + 1:]
        else:
            ciclo = solucao.ciclo[:j] + [solucao.ciclo[i]] + solucao.ciclo[j:i] + solucao.ciclo[i + 1:]
        return ciclo

    def melhor_vizinho(self, solucao: Solucao, distancias: tuple, tabu: set) -> Solucao:
        melhor_qualidade = math.inf
        imelhor = -1
        jmelhor = -1
        for i in range(solucao.tamanho-1):
            if i not in tabu:
                for j in range(solucao.tamanho-1):
                    if j < i and i - j == 1:  # evitar testar swap duas vezes
                        continue
                    if j != i and j not in tabu:
                        qualidade = self.computar_qualidade(solucao, distancias, i, j)
                        if qualidade < melhor_qualidade:
                            melhor_qualidade = qualidade
                            imelhor = i
                            jmelhor = j
        return Solucao(melhor_qualidade, self.gerar_novo_ciclo(solucao, imelhor, jmelhor), solucao.tamanho, imelhor, jmelhor)

    def primeiro_vizinho_melhor(self, solucao: Solucao, distancias: tuple, tabu: set) -> Solucao:
        melhor_qualidade = solucao.qualidade
        for i in range(solucao.tamanho-1):
            if i not in tabu:
                for j in range(solucao.tamanho-1):
                    if j < i and i - j == 1:  # evita teste swap i,j vizinhos duas vezes
                        continue
                    if j != i and j not in tabu:
                        qualidade = self.computar_qualidade(solucao, distancias, i, j)
                        if qualidade < melhor_qualidade:
                            return Solucao(qualidade, self.gerar_novo_ciclo(solucao, i, j), solucao.tamanho, i, j)
        return solucao


class AlgoritmoBusca:
    def __init__(self, nome):
        self.nome = nome

    @abstractmethod
    def buscar_solucao(self, solucao: Solucao, distancias: tuple, tempo_limite: float, vizinhanca: Vizinhanca) -> int:
        pass


class BuscaLocalMelhorMelhora(AlgoritmoBusca):
    def __init__(self):
        super().__init__("BLMM")

    def buscar_solucao(self, solucao: Solucao, distancias: tuple, tempo_limite: float, vizinhanca: Vizinhanca) -> int:
        melhor_qualidade = solucao.qualidade
        while time.time() < tempo_limite:
            solucao = vizinhanca.melhor_vizinho(solucao, distancias, set())
            if solucao.qualidade < melhor_qualidade:
                melhor_qualidade = solucao.qualidade
            else:  # não houve melhoras
                break
        return melhor_qualidade


class BuscaLocalPrimeiraMelhora(AlgoritmoBusca):
    def __init__(self):
        super().__init__("BLPM")

    def buscar_solucao(self, solucao: Solucao, distancias: tuple, tempo_limite: float, vizinhanca: Vizinhanca) -> int:
        melhor_qualidade = solucao.qualidade
        while time.time() < tempo_limite:
            solucao = vizinhanca.primeiro_vizinho_melhor(solucao, distancias, set())
            if solucao.qualidade < melhor_qualidade:
                melhor_qualidade = solucao.qualidade
            else:  # não houve melhoras
                break
        return melhor_qualidade


class BuscaTabu(AlgoritmoBusca):
    def __init__(self):
        super().__init__("BT")

    def buscar_solucao(self, solucao: Solucao, distancias: tuple, tempo_limite: float, vizinhanca: Vizinhanca) -> int:
        tamanho = len(distancias)
        melhor_qualidade = solucao.qualidade
        tabu = set()
        tabu_mandato = list()
        mandato = round(parametro_mandato/tamanho)
        qtd_trocas = vizinhanca.qtd_trocas
        while time.time() < tempo_limite:
            solucao = vizinhanca.melhor_vizinho(solucao, distancias, tabu)
            tabu.add(solucao.i_movimento)
            tabu_mandato.append(solucao.i_movimento)
            if qtd_trocas == 2:
                tabu.add(solucao.j_movimento)
                tabu_mandato.append(solucao.j_movimento)
            if solucao.qualidade < melhor_qualidade:
                melhor_qualidade = solucao.qualidade
            if mandato == 0:
                tabu.remove(tabu_mandato.pop(0))
                if qtd_trocas == 2:
                    tabu.remove(tabu_mandato.pop(0))
            else:
                mandato -= 1
        return melhor_qualidade


def ler_arquivo(instancia: str) -> tuple:
    with open('instancias/' + instancia + '.csv', 'r') as arquivo:
        leitor = csv.reader(arquivo, quoting=csv.QUOTE_NONNUMERIC, delimiter=",")
        distancias = tuple(map(tuple, leitor))
        return distancias


def computar_metricas(resultados_amostras: list) -> tuple[int, float, int]:
    qualidades, tempos = zip(*resultados_amostras)
    qualidade_media, tempo_medio = sum(qualidades) / amostras, sum(tempos) / amostras
    qualidade_desvio = statistics.stdev(qualidades, qualidade_media)
    qualidade_media, qualidade_desvio, tempo_medio = round(qualidade_media), round(qualidade_desvio, 2), round(tempo_medio)
    return qualidade_media, qualidade_desvio, tempo_medio


def escrever_resultados(resultados: list) -> None:
    # cabecalho = ("instancia", "autoria", "algoritmo", "q-medio", "q-desvio", "t-medio")
    with open('resultados.csv', 'a', encoding='UTF8', newline='') as csvf:
        writer = csv.writer(csvf, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
        # writer.writerow(cabecalho)
        for i in resultados:
            writer.writerow(i)


def retornar_elementos(ciclo: list, i: int, j: int) -> tuple[int, int, int, int, int, int]:
    elemento_i = ciclo[i]
    elemento_j = ciclo[j]
    if i == 0:
        elemento_pre_i = 0  # Elemento 0 Fixo na Primeira Posição
    else:
        elemento_pre_i = ciclo[i - 1]
    if j == 0:
        elemento_pre_j = 0  # Elemento 0 Fixo na Primeira Posição
    else:
        elemento_pre_j = ciclo[j - 1]
    if i == len(ciclo) - 1:
        elemento_pos_i = 0  # Elemento 0 Fixo na Primeira Posição
    else:
        elemento_pos_i = ciclo[i + 1]
    if j == len(ciclo) - 1:
        elemento_pos_j = 0  # Elemento 0 Fixo na Primeira Posição
    else:
        elemento_pos_j = ciclo[j + 1]
    return elemento_pre_i, elemento_i, elemento_pos_i, elemento_pre_j, elemento_j, elemento_pos_j


def gerar_solucao_inicial_aleatoria(tamanho: int, distancias: tuple) -> Solucao:
    ciclo = list(range(1, tamanho))  # Elemento 0 fixo na primeira posição
    random.shuffle(ciclo)
    qualidade = computar_qualidade_completa(ciclo, distancias)
    solucao = Solucao(qualidade, ciclo, tamanho, 0, 0)
    return solucao


def computar_qualidade_completa(ciclo: list, distancias: tuple) -> int:
    iterator = iter(ciclo)
    elemento_pre = next(iterator)
    qualidade = distancias[0][elemento_pre]  # Elemento 0 fixo no início da solução
    for elemento in iterator:
        qualidade += distancias[elemento_pre][elemento]
        elemento_pre = elemento
    qualidade += distancias[0][elemento_pre]  # Fechando ciclo
    return qualidade


# Constantes/Parâmetros Fixos
arquivos = ('wi29', 'dj38', 'qa194', 'uy734', 'zi929')
instancias = ("Western Sahara", "Djibouti", "Qatar", "Uruguay", "Zimbabwe")
amostras = 10
parametro_mandato = 5  # tamanho da instância / parâmetro mandato


def main(parametro_tempo: float, vizinhanca: Vizinhanca, algoritmo_busca: AlgoritmoBusca, autoria: str):
    resultados_finais = []
    for idx, arquivo in enumerate(arquivos):
        distancias = ler_arquivo(arquivo)
        tamanho = len(distancias)
        tempo_limite = tamanho * parametro_tempo
        resultados_amostras = []
        print("Instância: ", instancias[idx])
        for am in range(amostras):
            print("Executando amostra: ", am+1)
            # Início da busca heurística
            tempo_inicial = time.time()
            solucao = gerar_solucao_inicial_aleatoria(tamanho, distancias)
            melhor_qualidade = algoritmo_busca.buscar_solucao(solucao, distancias, tempo_limite+tempo_inicial, vizinhanca)
            tempo_execucao = time.time() - tempo_inicial
            resultados_amostras.append((melhor_qualidade, tempo_execucao))
        qualidade_media, qualidade_desvio, tempo_medio = computar_metricas(resultados_amostras)
        resultados_finais.append((instancias[idx], autoria, algoritmo_busca.nome+vizinhanca.nome, qualidade_media, qualidade_desvio, tempo_medio))
    escrever_resultados(resultados_finais)


# Rotina de Execução
main(0.06, Vizinhanca2opt(), BuscaLocalMelhorMelhora(), "Felipe")
main(0.06, Vizinhanca2opt(), BuscaLocalPrimeiraMelhora(), "Felipe")
main(0.06, Vizinhanca2opt(), BuscaTabu(), "Felipe")
main(0.06, VizinhancaShift(), BuscaLocalMelhorMelhora(), "Felipe")
main(0.06, VizinhancaShift(), BuscaLocalPrimeiraMelhora(), "Felipe")
main(0.06, VizinhancaShift(), BuscaTabu(), "Felipe")
main(0.12, Vizinhanca2opt(), BuscaLocalMelhorMelhora(), "Felipe.2t")
main(0.12, Vizinhanca2opt(), BuscaLocalPrimeiraMelhora(), "Felipe.2t")
main(0.12, Vizinhanca2opt(), BuscaTabu(), "Felipe.2t")
main(0.12, VizinhancaShift(), BuscaLocalMelhorMelhora(), "Felipe.2t")
main(0.12, VizinhancaShift(), BuscaLocalPrimeiraMelhora(), "Felipe.2t")
main(0.12, VizinhancaShift(), BuscaTabu(), "Felipe.2t")
