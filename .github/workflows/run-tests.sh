#!/bin/sh
# Author: Saira Hussain <saira.h0213@zoho.com>

# Run the reproducible suite
hisat2-build example/reference/22_20-21M.fa --snp example/reference/22_20-21M.snp 22_20-21M_snp

# Aligning example reads
hisat2 -f -x example/index/22_20-21M_snp -U example/reads/reads_1.fa -S eg1.sam

# Paired-end example
hisat2 -f -x example/index/22_20-21M_snp -1 example/reads/reads_1.fa -2 example/reads/reads_2.fa -S eg2.sam
hisat2 -f -x example/index/22_20-21M_snp -1 example/reads/reads_1.fa -2 example/reads/reads_2.fa -S eg2.sam

# Convert to BAM
samtools view -bS eg2.sam > eg2.bam

# Sort the BAM file
samtools sort eg2.bam -o eg2.sorted.bam

# Generate the variant
bcftools mpileup -f example/reference/22_20-21M.fa eg2.sorted.bam | bcftools view - > eg2.raw.bcf

# View the variant
bcftools view eg2.raw.bcf
