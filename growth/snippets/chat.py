#! /usr/bin/env python

import json
import logging
import sys

import transformers
from dotenv import load_dotenv
from haystack import Document
from haystack.components.embedders import (
    SentenceTransformersDocumentEmbedder,
    SentenceTransformersTextEmbedder,
)
from haystack.components.retrievers.in_memory import InMemoryEmbeddingRetriever
from haystack.document_stores.in_memory import InMemoryDocumentStore

# Env:
#  TOKENIZERS_PARALLELISM=false
load_dotenv()
logger = logging.getLogger(__name__)


class ThoughtfulChat:
    """Q&A chat fine-tuned with pre-existing answers."""

    MIN_SCORE: float = 0.5  # similar questions above this score will be accepted

    def __init__(self, qna_path: str):
        self._retriever = self._init_retriever(qna_path)
        self._language_model = transformers.pipeline(
            "text-generation", model="gpt2", max_length=128, truncation=True
        )
        self._text_embedder = SentenceTransformersTextEmbedder()
        self._text_embedder.warm_up()

    @staticmethod
    def _init_retriever(qna_path: str) -> InMemoryEmbeddingRetriever:
        try:
            with open(qna_path, "r") as file:
                questions = json.load(file)["questions"]
        except FileNotFoundError as exc:
            logger.error(f"Couldn't load Q&A file path due to: {exc}")
            questions = []

        documents = [
            Document(content=item["answer"], meta={"question": item["question"]})
            for item in questions
        ]
        doc_embedder = SentenceTransformersDocumentEmbedder()
        doc_embedder.warm_up()
        docs_with_embeddings = doc_embedder.run(documents)["documents"]
        document_store = InMemoryDocumentStore()
        document_store.write_documents(docs_with_embeddings)
        return InMemoryEmbeddingRetriever(document_store)

    def _search_hardcoded_answer(self, query: str) -> str | None:
        query_embedding = self._text_embedder.run(query)["embedding"]
        docs = self._retriever.run(query_embedding=query_embedding, top_k=1)[
            "documents"
        ]
        if not docs:
            return None

        # Just in case we deal with more docs.
        doc = max(docs, key=lambda doc: doc.score)
        return doc.content if doc.score > self.MIN_SCORE else None

    def get_response(self, query: str) -> str:
        """Generate a response based on the input user query."""
        # Step 1: Try to find a hardcoded answer.
        answer = self._search_hardcoded_answer(query)
        if answer:
            return f"Answer: {answer}"

        # Step 2: Generate a response from the language model if no hardcoded answer
        #  is found.
        generated_response = self._language_model(query)[0]["generated_text"]
        return f"LLM Reply: {generated_response}"


def main(args) -> int:
    if len(args) != 2:
        print(f"Usage: {args[0]} QUESTIONS_PATH")
        return 1

    chat = ThoughtfulChat(args[1])
    print("Welcome to Thoughtful conversational agent (type 'exit' to quit)")
    while True:
        user_input = input("> ")
        if user_input.lower() == "exit":
            break
        response = chat.get_response(user_input)
        print(response)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
