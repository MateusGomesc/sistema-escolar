/* 
	Criado por Mateus Gomes Costa
	
	Última atualização: 21/07/2023
*/
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>

void Cabecalho(char texto[]){
	system("cls");
	printf("-------------------------------------------------------\n");
	printf("      \033[33m%-48s\033[m|\n", texto);
	printf("-------------------------------------------------------\n\n");
}

void MenuTurmas(){
	puts("Selecione a turma:\n");
	puts("[1] 1º EM");
	puts("[2] 2º EM");
	puts("[3] 3º EM\n");
}

void MenuTrimestres(FILE *Lista){
	int TamanhoArq, i, *Contador;
	char *Nome;
	float *Trimestres;
	
	//define arrays
	Nome = (char*) calloc(40, sizeof(char));
	Trimestres = (float*) calloc(3, sizeof(float));
	Contador = (int*) calloc(3, sizeof(int));
	
	Cabecalho("Trimestres");
	puts("\033[31mATENÇÃO\033[m: é nescessário preencher as notas na ordem dos trimestres. O trimestre só será liberado assim que seu anterior for preenchido!\n");
	
	//recebe tamanho do arquivo para o laço
	TamanhoArq = Linefile(Lista);
	
	//verifica se trimeste está preenchido
	for(i=0; i<TamanhoArq; i++){
		if(i==0){
			fseek(Lista, 0, SEEK_SET);
		}
		
		fscanf(Lista, "%s %f %f %f", Nome, Trimestres[0], Trimestres[1], Trimestres[2]);
		
		if(Trimestres[0] == 0 && Trimestres[1] == 0 && Trimestres[2] == 0){
			Contador[0]++;
		}
		else if(Trimestres[0] != 0 && Trimestres[1] == 0 && Trimestres[2] == 0){
			Contador[1]++;
		}
		else if(Trimestres[0] != 0 && Trimestres[1] != 0 && Trimestres[2] == 0){
			Contador[2]++;
		}
	}
	
	//imprime tela de acordo com o que está preenchido
	if(Contador[0] == TamanhoArq || Contador[0] < TamanhoArq){
		puts("[1] 1º trimestre.");
	}
	else if(Contador[1] == TamanhoArq){
		puts("[1] 1º trimestre.");
		puts("[2] 2º trimestre.");
	}
	else if(Contador[2] == TamanhoArq){
		puts("[1] 1º trimestre.");
		puts("[2] 2º trimestre.");
		puts("[3] 3º trimestre.");
	}
	
	//libera arrays da memória
	free(Nome);
	free(Trimestres);
}

int RetornoMenu(int Controle){
	//retorno para o MENU
	while(1){
		if(!Controle){
			puts("\n\nDigite enter para voltar ao MENU...");
			getchar();
			
			if(getchar() != '\n')
				continue;
			else
				break;
		}
	}
	
	return -1;
}

int VerificaArq(FILE *arq){
	if(arq == NULL){
		puts("ERRO: não foi possível abrir a lista de alunos!");
		exit(1);
	}
}

int Linefile(FILE *arquivo){
	setlocale(LC_ALL, "Portuguese");
	
	int NumLinhas = 0;
	char Caractere;
	
	while((Caractere = fgetc(arquivo)) != EOF){
		if(Caractere == '\n')
			NumLinhas++;
	}
	
	return NumLinhas;
}

int main(void){
	setlocale(LC_ALL, "Portuguese");
	
	//cria estrutura de cadastro do aluno
	typedef struct{
		char *Nome;
		float *Nota;
	}CadastroAluno;
	
	//variáveis
	int QuantidadeAlunos, QuantidadeAlunosLista, QuantidadeAlunosAcrescentar, OpcMenu, i, ControleFechamentoArq;
	char *AlunoMaiorNota, *AlunoLista;
	float MaiorNota, Nota;
	CadastroAluno Aluno;
	FILE *ListaAlunos;
	
	//cria arrays na memória
	Aluno.Nome = (char*) calloc(40, sizeof(char));
	AlunoMaiorNota = (char*) calloc(40, sizeof(char));
	AlunoLista = (char*) calloc(40, sizeof(char));
	Aluno.Nota = (float*) calloc(4, sizeof(float));
	
	//início do programa
	while(1){
		Cabecalho("Virtual School");
		printf("\033[33m[1]\033[m Cadastrar Nota.\n");
		printf("\033[33m[2]\033[m Adicionar alunos a lista.\n");
		printf("\033[33m[3]\033[m Tabela de alunos cadastrados.\n");
		printf("\033[33m[4]\033[m Procurar aluno com maior nota.\n");
		printf("\033[33m[5]\033[m Sair do programa.\n\n");
		printf("Opção: \033[33m");
		scanf("%d", &OpcMenu);
		printf("\033[m");
		
		//encerra programa
		if(OpcMenu == 5){
			Cabecalho("Virtual School");
			puts("Encerrando...");
			sleep(3);
			exit(1);
		}
		
		switch(OpcMenu){
			case 1: //cadastrar notas
				Cabecalho("Turmas");
				
				//recebe turma
				MenuTurmas();
				printf("Opção: ");
				scanf("%d", &OpcMenu);
				
				//abre lista de alunos para escrita binaria
				switch(OpcMenu){
					case 1:
						ListaAlunos = fopen("1_EM.txt", "r+");
						VerificaArq(ListaAlunos);
						break;
					case 2:
						ListaAlunos = fopen("2_EM.txt", "r+");
						VerificaArq(ListaAlunos);
						break;
					case 3:
						ListaAlunos = fopen("3_EM.txt", "r+");
						VerificaArq(ListaAlunos);
				}
				
				//recebe trimestre
				MenuTrimestres(ListaAlunos);
				printf("\nOpção: ");
				scanf("%d", &OpcMenu);
				
				//insere as notas de acordo com o trimestre
				switch(OpcMenu){
					case 1:
						Cabecalho("Inserção de notas - 1º Tri.");
						//recebe dados e guarda no arquivo
						for(i=0; i<Linefile(ListaAlunos); i++){
							puts("Entrou");
							if(i==0)
								//leva cursor ao inicio do arquivo
								fseek(ListaAlunos, 0, SEEK_SET);
							
							//escaneia nome do aluno
							fscanf(ListaAlunos, "%s", Aluno.Nome);
							
							//recebe nota do primeiro trimestre
							printf("%s: ", Aluno.Nome);
							scanf("%f", Aluno.Nota[0]);
							
							//leva cursor para frente do nome
							fseek(ListaAlunos, sizeof(Aluno.Nome), SEEK_SET);
							
							//salva dados no arquivo
							fprintf(ListaAlunos, "%.2f", Aluno.Nota[0]);
						}
						break;
					case 2:
						break;
					case 3:
						break;
					default:
						puts("Opção Inválida!");
						exit(1);
				}
				
				//fecha lista de alunos para escrita
				ControleFechamentoArq = fclose(ListaAlunos);
				
				//mensagem de ok
				if(!ControleFechamentoArq)
					puts("Lista criada com sucesso!");
				
				//retorno para o MENU
				if(RetornoMenu(ControleFechamentoArq) == -1)
					continue;
				
			case 2: //adicionar alunos na lista
				Cabecalho("Adicionar alunos");
				//recebe quantidade de alunos
				printf("Digite a quantidade de alunos: ");
				scanf("%d", &QuantidadeAlunosAcrescentar);
				
				//abre arquivo para append binário
				ListaAlunos = fopen("ListaAlunos.txt", "ab");
				VerificaArq(ListaAlunos);
				
				Cabecalho("Adicionar alunos");
				//laço para adição das informações
				for(i=0; i<QuantidadeAlunosAcrescentar; i++){
					printf("Aluno %i\n", i+1);
					
					//recebe nome
					printf("Nome: ");
					fflush(stdin); fgets(Aluno.Nome, 40, stdin);
					
					//recebe nota final
					printf("Nota Final: ");
					scanf("%f", &Aluno.Nota);
					printf("\n\n");
					
					//salva dados no arquivo
					fprintf(ListaAlunos, "%s %.2f", Aluno.Nome, Aluno.Nota);				
				}
				
				//fecha o arquivo
				ControleFechamentoArq = fclose(ListaAlunos);
				
				//mensagem de ok
				if(!ControleFechamentoArq)
					puts("Alunos adicinados com sucesso!");
				
				//retorno para o MENU
				if(RetornoMenu(ControleFechamentoArq) == -1)
					continue;
			case 3:
				Cabecalho("Tabela de alunos");
				
				//abre o arquivo para leitura
				ListaAlunos = fopen("ListaAlunos.txt", "rb");
				VerificaArq(ListaAlunos);
				
				//mostra tabela
				QuantidadeAlunosLista = Linefile(ListaAlunos);

				for(i=0; i<QuantidadeAlunosLista; i++){
					if(i==0){
						//recebe dados da primeira linha
						fseek(ListaAlunos, 0, SEEK_SET);
						fscanf(ListaAlunos, "%s %f", Aluno.Nome, &Aluno.Nota[3]);
						
						//mostra cabeçalho e primeira linha da tabela
						printf("     Aprovação: \033[32m60pts\033[m\n\n");
						printf("   -----------------------------------\n");
						printf("   | Nome           | Nota Final     |\n");
						printf("   |---------------------------------|\n");
						if(Aluno.Nota[3] >= 60)
							printf("   | %-15s| \033[32m%6.2f\033[m         |\n", Aluno.Nome, Aluno.Nota[3]);
						else
							printf("   | %-15s| \033[31m%6.2f\033[m         |\n", Aluno.Nome, Aluno.Nota[3]);
					}
					else{
						//recebe dados das linhas subsequentes
						fscanf(ListaAlunos, "%s %f\n", Aluno.Nome, &Aluno.Nota[3]);
						
						//mostra linhas subsequentes
						if(Aluno.Nota[3] >= 60)
							printf("   | %-15s| \033[32m%6.2f\033[m         |\n", Aluno.Nome, Aluno.Nota[3]);
						else
							printf("   | %-15s| \033[31m%6.2f\033[m         |\n", Aluno.Nome, Aluno.Nota[3]);
						
						if(i == QuantidadeAlunosLista - 1){
							printf("   -----------------------------------\n");
						}
					}
				}
				
				ControleFechamentoArq = fclose(ListaAlunos);
				
				//retorno para o MENU
				if(RetornoMenu(ControleFechamentoArq) == -1)
					continue;				
			case 4: //aluno com maior nota
				Cabecalho("Maior nota");
				puts("Procurando...\n");
				sleep(2);
				
				//abre o arquivo para leitura binaria
				ListaAlunos = fopen("ListaAlunos.txt", "rb");
				
				if(ListaAlunos == NULL){
					puts("ERRO: não foi possível abrir a lista de alunos!");
					exit(1);
				}
				
				//seta parada para o laço
				QuantidadeAlunosLista = Linefile(ListaAlunos);
				
				//Laço procura aluno com maior nota
				for(i=0; i<QuantidadeAlunosLista; i++){
					if(i==0){
						//leva para o inicio do arquivo e recebe os dados
						fseek(ListaAlunos, 0, SEEK_SET);
						fscanf(ListaAlunos, "%s %f", AlunoLista, &Nota);
						
						//seta variáveis no primeiro laço
						strcpy(AlunoMaiorNota, AlunoLista);
						MaiorNota = Nota;
					}
					else{
						//fica no luga atual do arquivo pois fscanf lê até a quebra de linha e recebe dados
						fseek(ListaAlunos, 1, SEEK_CUR);
						fscanf(ListaAlunos, "%f %s", &Nota, AlunoLista);
						
						//acha o maior
						if(Nota > MaiorNota){
							strcpy(AlunoMaiorNota, AlunoLista);
							MaiorNota = Nota;
						}
					}
				}
				
				printf("Aluno: %s\nNota: %.2f", AlunoMaiorNota, MaiorNota);
				
				//retorno para o MENU
				ControleFechamentoArq = 0;
				if(RetornoMenu(ControleFechamentoArq) == -1)
					continue;
			default:
				puts("Opção inválida!");
				exit(1);	
		}
	}
	
	//libera strings da memória
	free(Aluno.Nome);
	free(AlunoLista);
	free(AlunoMaiorNota);
	
	return 0;
}
