# nlantau, 2020-07-16
""" PDF to text

Usage: to get large english text file 
for frequency analysis in Exercise 7
"""

from PyPDF2 import PdfFileReader, PdfFileWriter


def read_pdf(pdf_file, pages):
    with open(pdf_file, "rb") as f:
        pdf = PdfFileReader(f)
        for i in range(1, pages):
            page = pdf.getPage(i)
            text = page.extractText()
            yield text


if __name__ == "__main__":
    path = r"/Users/nlantau/test_3.txt"
    pdf_file = r"/Users/nlantau/stall3.pdf"

    gen = read_pdf(pdf_file, 500)
    with open(path, "w") as writer:
        for i in gen:
            writer.write(i)

